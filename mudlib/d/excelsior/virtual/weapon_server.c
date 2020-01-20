//    A virtual server for forged weapons.
//    The file is of the format: "<weapon-name>_<qual>.weapon"
//    Weapon types are parsed from a text file /d/damned/data/weapon_types
//
//    DarkeLIB 0.1
//    -Diewarzau 8/14/95

#include <std.h>
#include <daemons.h>

inherit "/std/virtual/compile";
inherit WEAPON;

void virtual_setup(string arg);

void create() {
  seteuid(getuid(this_object()));
  ::create();
  return;
}

void virtual_setup(string arg) {
  int qual, i, l_num, val;
  float f_val;
  string type, tmp, tmp2, line, func, *args;
  status flag;
  object db;

  if(sscanf(arg, "%s_%d", type, qual) != 2) {
    remove();
    return;
  }
  type = lower_case(type);
  set_name(replace_string(type, "-", ""));
  set_quality(qual);
  set("id", ({ type }) );
  l_num = 0;
  flag = 0;
  func = 0;
  tmp = "";
  seteuid(getuid());
db = find_object_or_load("/wizards/excelsior/virtual/weapon_db");
  while(line = (string)db->query_line(l_num)) {
    l_num++;
    if(!strlen(line) || line[0] == '#') continue;
    if(sscanf(line, "(%s):%*s", tmp2) == 2) {
      if(flag) line = "end:::";
      else if(tmp2 == type) {
	flag = 1;
      	continue;
      }
    }
    if(!flag) continue;
    if(sscanf(line,"%s:::%*s", tmp2) == 2) {
      if(!func) {
	func = tmp2;
	continue;
      }
      tmp = replace_string(tmp, "\n", " ");
      tmp = replace_string(tmp, func+":::", "");
      args = explode(tmp, ";");
      if(func == "value" && sizeof(args) &&
	 intp(val = REFS_D->resolv_str(args[0])))
	args[0] = sprintf("%d", to_int(to_float(val) *
                                       pow(1.5, to_float(query_quality()
							 - 2))));
      if(func == "float_val" && sizeof(args) &&
	 floatp(f_val = REFS_D->resolv_str(args[0])))
	args[0] = sprintf("%f", f_val * pow(2.0, to_float(query_quality()
							  -2)));
      switch(sizeof(args)) {
      case 0:
	call_other(this_object(), "set_"+func);
	break;
      case 1:
	call_other(this_object(), "set_"+func,
		   REFS_D->resolv_str(args[0]));
	break;
      case 2:
	call_other(this_object(), "set_"+func,
		   REFS_D->resolv_str(args[0]),
		   REFS_D->resolv_str(args[1]));
	break;
      case 3:
	call_other(this_object(), "set_"+func,
		   REFS_D->resolv_str(args[0]),
		   REFS_D->resolv_str(args[1]),
		   REFS_D->resolv_str(args[2]));
	break;
      case 4:
	call_other(this_object(), "set_"+func,
		   REFS_D->resolv_str(args[0]),
		   REFS_D->resolv_str(args[1]),
		   REFS_D->resolv_str(args[2]),
		   REFS_D->resolv_str(args[3]));
	break;
      default:
        continue;
      }
      if(tmp2 == "end") return;
      func = tmp2;
      tmp = "";
      continue;
    }
    if(!func) continue;
    tmp += line;
  }
  return;
}

