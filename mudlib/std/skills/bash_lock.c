inherit "/std/skills/skill";

function pick_func;
string name;
object shad;
object lock;
object weap;
int f_fac;
int inc;

void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(27);
    set_fast_dev_cost(79);
    set_property("prereq", "shield bash");
    set_property("no target", 1);
}

void info() {
message("help",
"This skill allows you to attempt to open locks the old-fashioned way.  "
"Beat the crap out of them.  Of course, this method is slightly more "
"error-prone than the more elegant methods employed by thieves.  "
"You may run the risk of breaking the lock, or worse, your weapon!  "
"You may use this skill in one of three ways:\n"
"  use bash lock at <lock>\n"
"	This is the default, takes a moderate amount of time, and has \n"
"	a mild chance of breaking the lock and/or your weapon.\n"
"  use bash lock at <lock> with little force\n"
"	This has no chance of breaking your weapon, and only a minute\n"
"	chance of breaking the lock.  Basically this represents attempting\n"
"	to use your weapon as a lock pick, and therefore it takes quite\n"
"	a long time.\n"
"  use bash lock at <lock> with great force\n"
"	This attempt is the involves the most risk of all, as you \n"
"	take a mighty whack at the lock.  It is almost instantaneous,\n"
"	but all but the most skilled run great risk of damaging the \n"
"	lock or their weapon.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int lock_lev, tm;
  object ob, ob2;
  string str1, force, *mess;

  if((time() - (int)from->query_last_use("bash lock")) < 550)
    {
    message("info", "You must rest a little longer before using this skill."
        , from);
    return;
  }
  if(sscanf(arg, "%s with %s", str1, force) == 2)
    arg = str1;
  else force = "default";
  ob = present(arg, environment(from));
  if(!ob && !environment(from)->query_locked(arg)) {
    message("info",
            "There is no locked door or object of that description here.",
            from);
    remove();
    return;
  }
  if(sizeof((object *)from->query_wielded()) < 1) {
    message("info", "You need to wield a weapon.", from);
    remove();
    return;
  }
  weap = ((object *)from->query_wielded())[0];
  if(from->query("lock picking")) {
    message("info", "You may only work on one lock at a time!", from);
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
    lock_lev = (int)ob->query_lock_level();
    name = lower_case((string)ob->query_short());
  } else {
    ob = environment(from);
    lock_lev = environment(from)->query_lock_level(arg);
    pick_func = (: call_other, environment(from), "set_locked" :);
    name = arg;
  }
  if((int)ob->query("lock broken "+name) == 1) {
    message("info", "The lock on "+name+" is damaged and cannot be bashed.",
	    from);
    remove();
    return;
  }
  lock = ob;
  seteuid(getuid());
  ob2 = new("/std/spells/shadows/move_shadow");
  ob2->set_move_func( (: call_other, this_object(), "int_skill" :) );
  ob2->set_move_arg(from);
  ob2->start_shadow(from);
  shad = ob2;
  from->set("lock picking", 1);
  switch(force) {
  case "great force":
    f_fac = 2;
    tm = 1;
    inc = 10;
    mess = ({ "%^CYAN%^You take a mighty whack at the lock!",
      ((string)from->query_cap_name() + " takes a mighty whack at the lock "+
	"on " + name +"!") });
    message("my_action", "%^CYAN%^You raise your weapon high above your head.",
	    from);
    message("other_action", (string)from->query_cap_name() +
	    " raises " + possessive(from) + " weapon high above "+
	    possessive(from) + "head.", environment(from), ({ from }));
    break;
  case "little force":
    f_fac = 1;
    tm = 15 - ((int)props["skill level"] / 7 - 7);
    inc = 60;
    mess = ({ "%^CYAN%^You jimmy the lock with your weapon.",
      ((string)from->query_cap_name() + " jimmies the lock on " + name +
       " with " + possessive(from) + " weapon.") });
    message("my_action", "%^CYAN%^You begin to jimmy the lock.", from);
    message("other_action", (string)from->query_cap_name() +
	    " begins to jimmy the lock on " + name + ".",
	    environment(from), ({ from }));
    break;
  case "default":
  default:
    f_fac = 0;
    tm = 19 - ((int)props["skill level"] / 7 - 5);
    inc = 25;
    mess = ({ "%^CYAN%^You pound on the lock with your weapon.",
      ((string)from->query_cap_name() + " pounds the lock on " + name +
       " with " + possessive(from) + " weapon.") });
    message("my_action", "%^CYAN%^You ready your weapon against the lock.",
	    from);
    message("other_action", (string)from->query_cap_name() +
	    " readies " + possessive(from) + " weapon against the lock on " +
	    name + ".",
	    environment(from), ({ from }));
    break;
  }
  call_out("bash_that_lock", inc, from, tm, mess);
  return;
}

void int_skill(object who) {
  if(!who || !objectp(who)) {
    remove();
    return;
  }
  remove_call_out("bash_that_lock");
  who->set("lock picking", 0);
  message("info", "%^CYAN%^You interrupt you lock-bashing efforts.", who);
  if(objectp(shad)) shad->external_destruct(shad);
  remove();
  return;
}

void bash_that_lock(object who, int time, string *mess) {
  string res;
  int roll;

  if(time > 0) {
    if(!present(weap, who)) {
      message("info", "%^CYAN%^You lost your weapon!\n%^CYAN%^"+
	      "You interrupt your efforts.", who);
      remove();
      return;
    }
    time--;
    message("my_action", mess[0], who);
    message("other_action", mess[1], environment(who), ({ who }) );
    switch(f_fac) {
    case 2:
      roll = random(100);
      if(roll < ((int)props["skill level"] / 10)) res = "success";
      else if((roll - (int)props["skill level"] / 10) > 40) {
	if(random(100) < 50) res = "weapon break";
	else res = "lock break";
      } else res = "fail";
      break;
    case 1:
      roll = random(100);
      if(roll < ((int)props["skill level"] / 11)) res = "success";
      else if(roll >= 93) {
        if(random(100) < 20) res = "weapon break";
        else res = "lock break";
      } else res = "continue";
      break;
    case 0:
    default:
      roll = random(200);
      if(roll < ((int)props["skill level"] / 11)) res = "success";
      else if(roll >= 170) {
        if(random(100) < 40) res = "weapon break";
        else res = "lock break";
      } else res = "continue";
      break;
    }
  } else res = "fail";
  switch(res) {
  case "fail":
    message("my_action", "%^CYAN%^You grow weary of bashing the lock and "+
	    "decide to stop.", who);
    who->set_last_use("bash lock");
    who->set("lock picking", 0);
    remove();
    return;
    break;
  case "lock break":
    message("my_action", "%^RED%^%^BOLD%^You damage the lock on "+name+"!  "+
	    "Further lock-bashing efforts will be useless.", who);
    message("other_action", (string)who->query_cap_name() + 
	    " inadvertently damages the lock on "+name+".",
	    environment(who), ({ who }) );
    if(lock)
      lock->set("lock break "+name, 1);
    who->set_last_use("bash lock");
    who->set("lock picking", 0);
    remove();
    return;
    break;
  case "weapon break":
    message("my_action", "%^RED%^%^BOLD%^You break your weapon!", who);
    message("other_action", (string)who->query_cap_name() +
    	    " breaks " + possessive(who) + " weapon while bashing the "+
	    " lock on "+name+"!",
	    environment(who), ({ who }) );
    if(weap) weap->remove();
    who->set_last_use("bash lock");
    who->set("lock picking", 0);
    remove();
    return;
    break;
  case "success":
    message("my_action", "%^BOLD%^%^CYAN%^The lock falls open!", who);
    message("other_action", (string)who->query_cap_name() +
          " opens the lock on "+name+".",
          all_inventory(environment(who)),
          ({ who }) );
    (*pick_func)(name, 0);
    if(shad) shad->external_destruct(shad);
    who->set("lock picking", 0);
    remove();
    return;
  case "continue":
  default:
    call_out("bash_that_lock", inc, who, time, mess);
    return;
  }
  return;
}

