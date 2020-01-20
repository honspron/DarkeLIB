//    A delayed function call manager.  More efficient
//    but less accurate than call_out.  Another ad-
//    vantage, since it uses heat_beat, it is some-
//    what lag-adjusted.
//
//    Diewarzau 4/2/96
//    DarkeLIB 0.1

#include <security.h>
#define WATCHDOG "/adm/daemon/watchdog_d"

mixed *all_functions, *queue;
int hb_on;
int debug;
int middle;

void create() {
  debug = 0;
  middle = 0;
  hb_on = 0;
  all_functions = ({});
  queue = ({});
  return;
}

void toggle_debug() { debug = !debug; }

varargs void add_function(object ob, string func, int delay, mixed arg1, mixed arg2, mixed arg3, mixed arg4) {
  int i;
  
  if(!ob || !func) {
//    if(debug && find_player("diewarzau"))
//      message("info", "Function not added.\n"+
//        sprintf("Object %O   func %s", ob, func),
//        find_player("diewarzau"));
    return;
  }
  i = sizeof(all_functions);
  if(!middle)
    all_functions +=
      ({ ({ delay, ob, func, arg1, arg2, arg3, arg4 }) });
  else
    queue += ({ ({ delay, ob, func, arg1, arg2, arg3, arg4 }) });
  hb_on = 1;
  set_heart_beat(1);
//  if(debug && find_player("diewarzau"))
//      message("info", "Function ADDED!\n"+
//        sprintf("Object %O   func %s\nsz before: %d, sz after: %d", ob, func, i,
//          sizeof(all_functions)),
//        find_player("diewarzau"));
  return;
}

void heart_beat() {
  int i, dly;
  object ob;
  string func, err, fname;
  mixed arg1, arg2, arg3, arg4, *functions_tmp;

  middle = 1;
  functions_tmp = ({});
  i = sizeof(all_functions);
  seteuid(UID_LOG);
//  if(debug && find_player("diewarzau"))
//      message("info", "Begin heartbeat.\n"+
//        sprintf("Size of list: %d", sizeof(all_functions)),
//        find_player("diewarzau"));
  while(i--) {
    if(sizeof(all_functions[i]) != 7) {
//      if(debug && find_player("diewarzau"))
//      message("info", "Function incorrect array size.\n"+
//        sprintf("Object %O   func %s", all_functions[i][1], all_functions[i][2]),
//        find_player("diewarzau"));
      continue;
    }
    if(!all_functions[i][1]) {
//      if(debug && find_player("diewarzau"))
//      message("info", "Object not found.\n"+
//        sprintf("func %s", all_functions[i][2]),
//        find_player("diewarzau"));
      continue;
    }
    fname = file_name(all_functions[i][1]);
    dly = all_functions[i][0];
    if(dly <= 0) {
//      if(debug && find_player("diewarzau"))
//      message("info", "Function COMPLETE.\n"+
//        sprintf("Object %O   func %s", all_functions[i][1], all_functions[i][2]),
//        find_player("diewarzau"));
      ob = all_functions[i][1];
      func = all_functions[i][2];
      arg1 = all_functions[i][3];
      arg2 = all_functions[i][4];
      arg3 = all_functions[i][5];
      arg4 = all_functions[i][6];
      if(arg4) {
        if(err=catch(call_other(ob, func, arg1, arg2, arg3, arg4)))
          log_file("delay_errors", "Error in delayed call: "+fname+"\n"+err+"\n");
      }
      else if(arg3) {
        if(err=catch(call_other(ob, func, arg1, arg2, arg3)))
          log_file("delay_errors", "Error in delayed call: "+fname+"\n"+err+"\n");
      }
      else if(arg2) {
        if(err=catch(call_other(ob, func, arg1, arg2)))
          log_file("delay_errors", "Error in delayed call: "+fname+"\n"+err+"\n");
      }
      else if(arg1) {
        if(err=catch(call_other(ob, func, arg1)))
          log_file("delay_errors", "Error in delayed call: "+fname+"\n"+err+"\n");
      }
      else {
        if(err=catch(call_other(ob, func)))
          log_file("delay_errors", "Error in delayed call: "+fname+"\n"+err+"\n");
      }
    }
    else {
      dly -= 2;
      all_functions[i][0] = dly;
      functions_tmp += ({ all_functions[i] });
    }
  }
//  if(debug && find_player("diewarzau"))
//      message("info", "End heart beat.\n"+
//        sprintf("Size of list: %d  Size of tmp list: %d\nSize of queue: %d",
//        sizeof(all_functions), sizeof(functions_tmp), sizeof(queue)),
//        find_player("diewarzau"));
  all_functions = functions_tmp;
  if(!all_functions) {
    hb_on = 0;
    set_heart_beat(0);
  }
  middle = 0;
  all_functions += queue;
  queue = ({});
  seteuid(getuid());
  WATCHDOG->reset_check();
  return;
}

void function_report() {
  string tmp, func, fname;
  object ob;
  mixed arg1, arg2, arg3, arg4;
  int i, to_go;

  tmp = "";
  i = sizeof(all_functions);
  if(!i) {
    write("There are no pending functions.");
    return;
  }
  while(i--) {
    if(sizeof(all_functions[i]) != 7) continue;
    ob = all_functions[i][1];
    if(!ob) continue;
    fname = file_name(ob);
    to_go = all_functions[i][0];
    func = all_functions[i][2];
    arg1 = all_functions[i][3];
    arg2 = all_functions[i][4];
    arg3 = all_functions[i][5];
    arg4 = all_functions[i][6];
    if(arg4) {
      tmp += sprintf("Function: %s  Object: %s  Dly: %d\n",
        func, fname, to_go);
      tmp += sprintf("Arg1: %O\nArg2: %O\nArg3: %O\nArg4: %O\n",
        arg1, arg2, arg3, arg4);
    } else if(arg3) {
      tmp += sprintf("Function: %s  Object: %s  Dly: %d\n",
        func, fname, to_go);
      tmp += sprintf("Arg1: %O\nArg2: %O\nArg3: %O\n",
        arg1, arg2, arg3);
    } else if(arg2) {
      tmp += sprintf("Function: %s  Object: %s  Dly: %d\n",
        func, fname, to_go);
      tmp += sprintf("Arg1: %O\nArg2: %O\n",
        arg1, arg2);
    } else if(arg1) {
      tmp += sprintf("Function: %s  Object: %s  Dly: %d\n",
        func, fname, to_go);
      tmp += sprintf("Arg1: %O\n",
        arg1);
    } else {
      tmp += sprintf("Function: %s  Object: %s  Dly: %d\n",
        func, fname, to_go);
      tmp += "No args.\n";
    }
    tmp += "\n";
  }
  this_player()->more(explode(tmp, "\n"));
  return;
}

void restart_heart() {
  hb_on = 1;
  set_heart_beat(1);
}

mixed *delayed_function_info() {
  int i;
  mixed *ret, *tmp;

  i = sizeof(all_functions);
  if(!i) return ({});
  ret = ({});
  while(i--) {
    tmp = allocate(7);
    tmp[0] = all_functions[i][1];
    if(!tmp[0]) continue;
    tmp[1] = all_functions[i][2];
    tmp[2] = all_functions[i][0];
    if(tmp[2] <= 0) continue;
    tmp[3] = all_functions[i][3];
    tmp[4] = all_functions[i][4];
    tmp[5] = all_functions[i][5];
    tmp[6] = all_functions[i][6];
    ret += ({ tmp });
  }
  return ret;
}

void remove_delayed_call(object ob, string func) {
  int i;

  i = sizeof(all_functions);
  if(!func) return;
  while(i--) {
    if(all_functions[i][1] != ob) continue;
    if(all_functions[i][2] == func) {
      all_functions = exclude_array(all_functions, i);
      return;
    }
  }
  return;
}

