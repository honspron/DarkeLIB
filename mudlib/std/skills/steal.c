#include "/adm/include/move.h"
#include "/adm/include/clock.h"

inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(15);
    set_fast_dev_cost(47);
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("prereq", "pick pocket");
}

void info() {
message("help",
"You may use this skill to steal an object from someone who is carrying it.  "+
"That object may not be wielded or worn if you want to steal it.  The skill "+
"is used one of two ways:\n"+
"    use steal at <who>			Steals a random object.\n"+
"    use steal at <who> with <what>	Steals <what>.\n"+
"\nNOTE: Repeated attempts at stealing from the same player will result "+
"in greater ease of detection!",
this_player());
}

int steal_filter(object what) {
  if(what->query_wielded()) return 0;
  if(what->query_worn()) return 0;
  if(what->query_property("no steal")) return 0;
  return 1;
}

void skill_func(object from, object at, string arg) {
  object *inv, what;
  int res, *tmp, bonus;

  inv = filter_array(all_inventory(at), "steal_filter", this_object());
  if(!sizeof(inv)) {
    message("info", capitalize(nominative(at)) +" has nothing you can steal.",
 	    from);
    remove();
    return;
  }
  if(environment(from) && environment(from)->query_property("no steal")) {
    message("my_action", "Divine forces prevent your action.", from);
    remove();
    return;
  }
  if(!arg || !strlen(arg)) what = inv[random(sizeof(inv))];
  else {
    what = present(arg, at);
    if(!what) {
      message("info", capitalize(nominative(at)) + " does not have "+
	      article(arg)+".", from);
      remove();
      return;
    }
    if(member_array(what, inv) < 0 || what->query_property("no steal")) {
      message("info", "You cannot steal that!", from);
      remove();
      return;
    }
  }
  tmp = (int *)at->query("per bonus:"+(string)from->query_name());
  if(!tmp) bonus = 0;
  else if(sizeof(tmp) != 2) bonus = 0;
  else if((time() - tmp[1]) > (2*HOUR)) bonus = 0;
  else bonus = tmp[0];
  res = skill_contest(props["skill level"], (int)at->query_skill("perception")
		      + bonus,
		      1);
  at->set("per bonus:"+(string)from->query_name(),
	  ({ bonus + 7+random(7), time() }));
  message("my_action", "%^CYAN%^You carefully reach into "+
	  (string)at->query_cap_name()+"'s pockets...", from);
  call_out("do_steal", 5, res, ({ from, at, what }) );
  return;
}

void do_steal(int res, object *obs) {
  object from, at, what;

  if(sizeof(obs) != 3) {
    message("shout", "BUG IN STEAL SKILL....", users());
    remove();
    return;
  }
  from = obs[0];
  at = obs[1];
  what = obs[2];
  if(!present(at, environment(from))) {
    remove();
    return;
  }
  if(res == 2 || res == 0) {
    message("my_action", "%^RED%^You're BUSTED!!!%^RESET%^\n"+
	    (string)at->query_cap_name()+ " angrily attacks you!",
	    from);
    message("other_action", "%^RED%^You just caught "+
	    (string)from->query_cap_name()+" trying to steal "+
	    lower_case((string)what->query_short()) + " from you !\n",
	    at);
    message("other_action", (string)from->query_cap_name() + 
	    " just tried to steal "+
	    lower_case((string)what->query_short()) + " from "+
	    (string)at->query_cap_name()+".",
            environment(at), ({ from, at }));

  if((string)at->query_catch() == "off")
    message("other_action", "%^RED%^You catch is off so you did not attack "+
             (string)from->query_cap_name()+"\n.", at);
     else 
           at->kill_ob(from, 0); 
    remove();
    return;
  }
  if((int)what->move(from) != MOVE_OK) {
    message("info", "You could not take "+
	    lower_case((string)what->query_short()) + " from "+
	    (string)at->query_cap_name()+", but "+
	    nominative(at)+ " didn't notice you trying.", from);
    remove();
    return;
  }
  message("my_action", "You deftly swipe "+
	  lower_case((string)what->query_short()) + " from "+
	  (string)at->query_cap_name()+", and "+
	   nominative(at)+ " is none the wiser.", from);
  remove();
  return;
}
