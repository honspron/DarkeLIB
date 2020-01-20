inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(15);
    set_fast_dev_cost(40);
    set_property("target type", "living");
    set_property("must be present",1);
}

void info() {
message("help",
"This skill may be used against enemies in combat.  If sucessful you jump "+
"up and kick your target."+
"  You may only use this skill once every 8 combat rounds.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int flag, i; 
  string *limbs;
  if((time() - (int)from->query_last_use("jump kick")) < 16)
    {
    message("info", "You are too tired to use this skill yet."
        , from);
    return;
  }
  from->set_last_use("jump kick");
  at->kill_ob(from, 0);
  props["skill level"] -= random(100);
  if((int)props["skill level"] < -10) {
    message("my_combat", "You jump up but miss  "+
            (string)at->query_cap_name()+ " miserably with your kick.",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " jumps up and misses you with a kick.", at);
    message("other_combat", (string)from->query_cap_name() +
            " jumps up and misses "+
            (string)at->query_cap_name()+ "with a kick.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();   
    return;
  }
  message("my_combat", "You jump up and kick "+
          (string)at->query_cap_name()+ ".",
          from);
  message("other_combat", (string)from->query_cap_name() +
          " jumps up and kicks you.", at);
  message("other_combat", (string)from->query_cap_name() +
          " jumps up and kicks "+
          (string)at->query_cap_name()+ ".",
          all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]
) {
  case -10..5:
    at->do_damage((string)at->return_target_limb(), random(8)+5);
    break;      
  case 6..39:
    at->do_damage((string)at->return_target_limb(), 2 * (random(10)+1));
    do_critical(from, at, "strike A");
    break;
  case 40..64:  
    at->do_damage((string)at->return_target_limb(), 2 * (random(9)+1));
    do_critical(from, at, "strike B");   
    break;
  case 65..84:
    at->do_damage((string)at->return_target_limb(), 2 * (random(8)+1));
    do_critical(from, at, "strike C");
    break;
  case 85..94:
    at->do_damage((string)at->return_target_limb(), 2 * (random(7)+1));
    do_critical(from, at, "strike D");
    break;
  case 95..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "strike E");
    break;
  }
  remove();     
  return;
}
