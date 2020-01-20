inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(7);
    set_fast_dev_cost(19);
    set_property("target type", "living");
    set_property("must be present",1);
}

void info() {
message("help",
"This skill may be used against enemies in combat.  If you are holding "+
"a shield, you may bash the opponent in addition to other attacks."+
"  You may only use this skill once every two combat rounds.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int flag, i, diff;
  string *limbs;

  if((time() - (int)from->query_last_use("shield bash")) < 4)
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
    message("info", "You may not shield-bash a target which is immaterial.",
            from);
    remove();
    return;
  }
  flag = 0;
  limbs = from->query_limbs();
  i = sizeof(limbs); 
  while(i--) 
    if(member_array("shield", (string *)from->query_armour(limbs[i]))
       > -1) flag = 1;
  if(!flag) {
    message("my_action", "You do not have a shield!", from);
    remove();
    return;
  }
  from->set_last_use("shield bash");
  at->kill_ob(from, 0);
  diff = props["skill level"] - at->query_skill("dodge");
  if ((random(100) + diff) < 35) {
        message("my_combat", "%^MAGENTA%^You attempt to bash but "+
            (string)at->query_cap_name()+ " dodges nimbly out of the way.%^RESET%^",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to bash you with "+possessive(from)+
            " shield but you nimbly dodge out of the way.", at);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to bash "+
            (string)at->query_cap_name()+ " with "+
            possessive(from)+ " shield but " +
	    (string)at->query_cap_name()+" dodges.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
  }
  props["skill level"] -= (random(100) + 
			   at->query_current_protection("torso","crushing")/4 );
  if((int)props["skill level"] < -10) {
    message("my_combat", "%^MAGENTA%^You attempt to bash "+
	    (string)at->query_cap_name()+ " but miss miserably.%^RESET%^",
	    from);
    message("other_combat", (string)from->query_cap_name() +
	    " attempts to bash you with "+possessive(from)+ 
	    " shield but misses.", at);
    message("other_combat", (string)from->query_cap_name() +
	    " attempts to bash "+
	    (string)at->query_cap_name()+ " with "+
	    possessive(from)+ " shield but misses.",
	    all_inventory(environment(from)),
	    ({ from, at }) );
    remove();
    return;
  }
  message("my_combat", "%^MAGENTA%^You bash "+
	  (string)at->query_cap_name()+ " fiercely with your shield.%^RESET%^",
	  from);
  message("other_combat", (string)from->query_cap_name() +
	  " unbalances you with a fierce bash from " +possessive(from)+
	  " shield.", at);
  message("other_combat", (string)from->query_cap_name() +
	  " delivers a nasty bash to "+
	  (string)at->query_cap_name()+ " with "+
	  possessive(from)+ " shield.",
	  all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]) {
  case -10..5:
    at->do_damage((string)at->return_target_limb(), random(8)+1);
    break;
  case 6..20:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "crushing A");
    break;
  case 21..33:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "crushing B");
    break;
  case 34..45:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "crushing C");
    break;
  case 46..62:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "crushing D");
    break;
  case 63..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "crushing E");
    break;
  }
  remove();
  return;
}

