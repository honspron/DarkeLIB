inherit "/std/skills/skill";

function pick_func;
mixed pick_arg;
string name;
object shad;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(19);
    set_fast_dev_cost(56);
    set_property("no target", 1);
    set_property("prereq", "consider lock");
}

void info() {
message("help",
"This skill allows you to open locks without the benefit of a key.  "+
"Of course, you will need to obtain some lock picks first." +
"  Note that some locks may take several minutes of real time to "+
"pick, especially if your skill is not good.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int lock_lev, time;
  object ob, ob2;

  ob = present(arg, environment(from));
  if(!ob && !environment(from)->query_locked(arg)) {
    message("info", 
	    "There is no locked door or object of that description here.",
	    from);
    remove();
    return;
  }
  if(!present("lock pick", from)) {
    message("info", "You need lock picks to do that!", from);
    remove();
    return;
  }
  if(from->query("lock picking")) {
    message("info", "You may only pick one lock at a time!", from);
    remove();
    return;
  }
  if(ob) {
    if(member_array("std/bag_logic.c", deep_inherit_list(ob))
       < 0) {
      message("info", "That doesn't have a lock.", from);
      remove();
      return;
    }
    if(!ob->query_locked()) {
      message("info", "It is not locked!", from);
      remove();
      return;
    }
    pick_func = (: call_other, ob, "pick_lock" :);
    pick_arg = from;
    lock_lev = (int)ob->query_lock_level();
lock_lev = lock_lev + 7;
    name = lower_case((string)ob->query_short());
  } else {
    lock_lev = environment(from)->query_lock_level(arg);
lock_lev = lock_lev + 7;
    pick_func = (: call_other, environment(from), "set_locked" :);
    pick_arg = arg;
    name = arg;
  }
  time = lock_lev;
  if(time < 1) time = 1;
  props["skill level"] -= 5*(lock_lev - 8)/4;
  switch(props["skill level"]) {
  case 96..115:
    props["skill level"] = 94;
    break;
  case 116..10000:
    props["skill level"] = 99;
  default:
  }
  seteuid(getuid());
  ob2 = new("/std/spells/shadows/move_shadow");
  ob2->set_move_func( (: call_other, this_object(), "int_skill" :) );
  ob2->set_move_arg(from);
  ob2->start_shadow(from);
  shad = ob2;
  message("info", "%^BOLD%^%^CYAN%^You begin working on the lock.", from);
  from->set("lock picking", 1);
  call_out("pick_lock", 60, from, (time - 1), lock_lev);
  return;
}

void int_skill(object who) {
  if(!who || !objectp(who)) {
    remove();
    return;
  }
  remove_call_out("pick_lock");
  who->set("lock picking", 0);
  message("info", "%^CYAN%^You interrupt you lock-picking efforts.", who);
  if(objectp(shad)) shad->external_destruct(shad);
  remove();
  return;
}

void show_progress(object who, int time, int progress)
{
  int percent;

  percent = (progress * 100)/time;
  switch(percent) {
  case 70..10000:
    message("info", "You have barely begun to crack this lock!", who);
    break;
  case 40..69:
    message("info", "You have made middling progress towards cracking this lock\
!", who);
    break;
  case 20..39:
    message("info", "You have made extremely good progress towards cracking thi\
s lock!", who);
    break;
  case 0..19:
    message("info", "You have all but defeated this lock!", who);
    break;
  default:
    message("info", "Error in picklocks!  Report to Mikus right away!", who);
  }

  return;
}

void pick_lock(object who, int time, int total) {
  object pick;
  int i;

  if(time > 0) {
    pick = present("lock pick", who);
    if(!pick) {
      message("info", "You lost your lock pick!", who);
      this_object()->int_skill(who);
      return;
    }
    message("my_action", "You fiddle with the lock.", who);
    message("other_action", (string)who->query_cap_name() +
	    " fiddles with the lock on "+name+".",
	    all_inventory(environment(who)),
	    ({ who }) );
    i = random(100);
    if(i < ((105-props["skill level"])/5) || i <= 1) {
      message("info", "%^BOLD%^%^RED%^Your lock pick breaks!", who);
      pick->remove();
      pick = present("lock pick", who);
      if (!present("lock pick", who)) {
	message("info", "You have no more lock picks!", who);
	this_object()->int_skill(who);
	return;
      }
      time = time + random((total - time)/2) + (total - time)/4;
      message("info", "%^BOLD%^%^RED%^You lost some progress!", who);
      show_progress(who, total, time);
    } else if(i < props["skill level"] / 4) {
      message("info", "You make very good progress with the lock.",
        who);
      time -= 3;
      who->add_exp2(200);
      show_progress(who, total, time);
    } else if(i < props["skill level"] / 2) {
      message("info", "You make a good deal of progress with the lock.",
        who);
      time -= 2;
      who->add_exp2(100);
      show_progress(who, total, time);
    } else if(i < props["skill level"]) {
      message("info", "You make some progress with the lock.",
        who);
      time --;
      who->add_exp2(50);
      show_progress(who, total, time);
    } else
      message("info", "You make no progress with the lock.",
        who);
    call_out("pick_lock", 60, who, time, total);
    return;
  }
  message("my_action", "%^BOLD%^%^CYAN%^You open the lock!", who);
  message("other_action", (string)who->query_cap_name() +
	  " opens the lock on "+name+".",
	  all_inventory(environment(who)),
          ({ who }) );
  (*pick_func)(pick_arg, 0);
  if(shad) shad->external_destruct(shad);
  who->set("lock picking", 0);
  remove();
  return;
}





