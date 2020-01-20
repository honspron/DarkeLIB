// Bummed from shield bash  ++Drizzt 8/3/96

inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(28);
    set_fast_dev_cost(83);
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("prereq", "kick");
}

void info() {
message("help",
"This skill may be used against enemies in combat. "+
" You may only use this skill once every two combat rounds.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int flag, i, diff;
  string *limbs;

  if((time() - (int)from->query_last_use("sweep")) < 4)
    {
    message("info", "You are too tired to use this skill yet."
        , from);
    return;
  }
  if(environment(from) &&
    environment(from)->query_property("no attack")) {
    message("info", "Mystic forces prevent your action.", from);
    remove();
    return ;
  }
  if(at->shadow_form() || at->query_ghost()) {
    message("info", "You may not sweep a target which is immaterial.",
            from);
    remove();
    return;
  }
  flag = 0;
  from->set_last_use("sweep");
  at->kill_ob(from, 0);
  diff = props["skill level"] - at->query_skill("dodge");
  if ((random(100) + diff) < 35) {
        message("my_combat", "%^MAGENTA%^You attempt to sweep but "+
            (string)at->query_cap_name()+ " dodges nimbly out of the way.%^RESET%^",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to kick your leg, but you nimbly dodge out of the way.", at);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to sweep "+
            (string)at->query_cap_name()+"'s leg, but " +
	    (string)at->query_cap_name()+" dodges.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
  }
  props["skill level"] -= (random(100) + 
		     at->query_current_protection("torso","crushing")/4 );
  if((int)props["skill level"] < -10) {
    message("my_combat", "%^MAGENTA%^You attempt to sweep "+
	    (string)at->query_cap_name()+ " but miss miserably.%^RESET%^",
	    from);
    message("other_combat", (string)from->query_cap_name() +
	    " attempts to sweep your leg.", at);
    message("other_combat", (string)from->query_cap_name() +
	    " attempts to sweep "+(string)at->query_cap_name()+"'s leg, but misses.",
	    all_inventory(environment(from)),
	    ({ from, at }) );
    remove();
    return;
  }
  message("my_combat", "%^MAGENTA%^You sweep "+
	  (string)at->query_cap_name()+"'s leg and he falls over.%^RESET%^",
	  from);
  message("other_combat", (string)from->query_cap_name() +
	  " sweeps your leg and you fall to the ground.", at);
  message("other_combat", (string)from->query_cap_name() +
	  " sweeps "+
	  (string)at->query_cap_name()+ "'s leg and "+
          (string)at->query_cap_name()+ " falls to the ground.",
	  all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]) {
  case -10..25:
    at->do_damage((string)at->return_target_limb(), random(6)+1);
    break;
  case 26..50:
    at->do_damage((string)at->return_target_limb(), 2 * (random(10)+1));
    do_critical(from, at, "crushing A");
    break;
  case 51..63:
    at->do_damage((string)at->return_target_limb(), 2 * (random(14)+1));
    do_critical(from, at, "crushing B");
    do_critical(from, at, "stun A");
    break;
  case 64..75:
    at->do_damage((string)at->return_target_limb(), 2 * (random(18)+1));
    do_critical(from, at, "crushing C");
    do_critical(from, at, "stun B");
    break;
  case 76..92:
    at->do_damage((string)at->return_target_limb(), 2 * (random(22)+1));
    do_critical(from, at, "crushing D");
    do_critical(from, at, "stun C");
    break;
  case 93..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(30)+1));
    do_critical(from, at, "crushing E");
    do_critical(from, at, "stun D");
    break;
  }
  remove();
  return;
}

