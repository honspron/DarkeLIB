#include "/adm/include/move.h"
#include "/adm/include/clock.h"

inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(11);
    set_fast_dev_cost(28);
    set_property("target type", "living");
    set_property("must be present",1);
}

void info() {
message("help",
"This skill is used to lift a small deal of cash from a player or monster.\n"+
"    use pick pocket at <who>\n"+
"\nNOTE: Repeated attempts at picking the same player's pocket will result "+
"in greater ease of detection!",
this_player());
}

void skill_func(object from, object at, string arg) {
  int res, *tmp, bonus;

  if(environment(from) && environment(from)->query_property("no steal")) {
    message("my_action", "Divine forces prevent your action.", from);
    remove();
    return;
  }
  if(from->query("pick pocket")) {
    message("info", "You can only do that once at a time!",
      from);
    remove();
    return;
  }
  tmp = (int *)at->query("per bonus:"+(string)from->query_name());
  if(!tmp) bonus = 0;
  else if(sizeof(tmp) != 2) bonus = 0;
  else if((time() - tmp[1]) > HOUR) bonus = 0;
  else bonus = tmp[0];
  res = skill_contest(props["skill level"], (int)at->query_skill("perception")
		      + bonus,
		      1);
  at->set("per bonus:"+(string)from->query_name(),
	  ({ bonus + 5+random(5), time() }));
  message("my_action", "%^CYAN%^You carefully reach into "+
	  (string)at->query_cap_name()+"'s pockets...", from);
	from->set("pick pocket", 1);
  call_out("do_steal", 5, res, ({ from, at }) );
  return;
}

void do_steal(int res, object *obs) {
  object from, at;
  string *currs, desc;
  int i, amt;

  if(sizeof(obs) != 2) {
    message("shout", "BUG IN PICKPOCKET SKILL....", users());
    remove();
    return;
  }
  from = obs[0];
  at = obs[1];
  from->set("pick pocket", 0);
  if(!present(at, environment(from))) {
    remove();
    return;
  }
  if(res == 2 || res == 0) {
    message("my_action", "%^RED%^You're BUSTED!!!%^RESET%^\n"+
	    (string)at->query_cap_name()+ " angrily attacks you!",
	    from);
    message("other_action", "%^RED%^You just caught "+
	    (string)from->query_cap_name()+" trying to pick "+
	    "your pockets!",
	    at);
    message("other_action", (string)from->query_cap_name() + 
	    " just tried to pick "+
	    (string)at->query_cap_name()+"'s pockets.",
	    environment(at), ({ from, at }));
    at->kill_ob(from, 0);
    remove();
    return;
  }
  currs = (string *)at->query_currencies();
  i = sizeof(currs);
  desc = "";
  while(i--) {
    amt = (int)at->query_money(currs[i]) / ((random (600)+700) / 
					    props["skill level"]);
    if(amt > 0 && i == 0) desc += sprintf(" %d %s",amt, currs[i]);
    else if(amt > 0 && i == 1) desc += sprintf(" %d %s and",amt,currs[i]);
    else if(amt > 0) desc += sprintf(" %d %s,",amt,currs[i]);
      at->add_money(currs[i], -1*amt);
      from->add_money(currs[i], amt);
  }
  message("info", "You swipe"+desc+" from "+(string)at->
          query_cap_name() + ", and "+nominative(at) +
          " is none the wiser.", from);
  remove();
  return;
}
