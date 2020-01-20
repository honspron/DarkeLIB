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
"This skill may be used against enemies in combat.  If sucessful, you"+
"suddenly knee your target in the middle of combat."+
"  You may only use this skill once every 5 combat rounds, but it is quite powerful.",
this_player());
}
 
void skill_func(object from, object at, string arg) {
 
  int flag, i;
  string *limbs;
  if((time() - (int)from->query_last_use("knee")) < 10)
    {
    message("info", "Your knee is a little sore to do that."
        , from);
    return;
  }
  from->set_last_use("knee");
  at->kill_ob(from, 0);
  props["skill level"] -= random(100);
  if((int)props["skill level"] < -10) {
    message("my_combat", "You raise your knee purposefully at  "+
            (string)at->query_cap_name()+ " but only hit thin air.",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " just misses you with a nasty-looking knee move.", at);
    message("other_combat", (string)from->query_cap_name() +
            " just misses "+
            (string)at->query_cap_name()+ "with a mean knee move.",
 
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
  }
  message("my_combat", "You raise your knee and give it to "+
          (string)at->query_cap_name()+ " in the groin. ",
          from);
  message("other_combat", (string)from->query_cap_name() +
          " smashes you in the groin with his knee.", at);
  message("other_combat", (string)from->query_cap_name() +
          " suddenly smashes "+
          (string)at->query_cap_name()+ " in the groin with his knee.",
          all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]
) {
  case -10..5:
    at->do_damage((string)at->return_target_limb(), random(20)+5);
    break; 
  case 6..39:
    at->do_damage((string)at->return_target_limb(), 2 * (random(20)+1));
    do_critical(from, at, "strike A");
    break;
  case 40..64:
    at->do_damage((string)at->return_target_limb(), 2 * (random(29)+1));
    do_critical(from, at, "strike B");
    break;
  case 65..84:
    at->do_damage((string)at->return_target_limb(), 2 * (random(28)+1));
    do_critical(from, at, "strike C");
    break;
  case 85..94:
    at->do_damage((string)at->return_target_limb(), 2 * (random(27)+1));
    do_critical(from, at, "strike D");
    break;
  case 95..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(26)+1));
    do_critical(from, at, "strike E");
    break;
  }
  remove();
  return;
}
