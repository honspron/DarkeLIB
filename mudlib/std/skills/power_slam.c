inherit "/std/skills/skill";
 
void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(20);
    set_fast_dev_cost(63);
    set_property("target type", "living");
    set_property("must be present",1);
}
 
void info() {
message("help",
"This skill may be used against enemies in combat. "+
" You may only use this skill once every two combat rounds."
" It lets the user slam into his or her opponent with a"
" powerful rush, possibly stunning them.",
this_player());
}
 
 
void skill_func(object from, object at, string arg) {
  int flag, i, diff;
  string *limbs;
 
  if((time() - (int)from->query_last_use("power slam")) < 4)
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
    message("info", "You may not power slam a target which is immaterial.",
            from);
    remove();
 
    return;
  }
  flag = 0;
  from->set_last_use("power slam");
  at->kill_ob(from, 0);
  diff = props["skill level"] - at->query_skill("dodge");
  if ((random(100) + diff) < 35) {
        message("my_combat", "You attempt to slam your opponent but "+
            (string)at->query_cap_name()+ " moves quickly out of the way.",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to slam you, but you move quickly out of the way.",
at);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to hit "+
            (string)at->query_cap_name()+", with a power slam but " +
            (string)at->query_cap_name()+" dodges.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
 
  }
  props["skill level"] -= (random(100) +
                     at->query_current_protection("torso","stun")/4 );
  if((int)props["skill level"] < -10) {
    message("my_combat", "You attempt to slam "+
            (string)at->query_cap_name()+ " with a surprise rush, but miss miserably.",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to hit you with a power slam.", at);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to hit "+(string)at->query_cap_name()+ ", with a power slam, but misses.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
  }
  message("my_combat", "You hit "+
          (string)at->query_cap_name()+ " with a powerful lunge forward and "+
          (string)at->query_cap_name()+ " smashes into the ground.",
          from);
 
  message("other_combat", (string)from->query_cap_name() +
          " power slams you and you hit the ground, hard.", at);
  message("other_combat", (string)from->query_cap_name() +
          " power slams "+
          (string)at->query_cap_name()+ " right in the gut and "+
          (string)at->query_cap_name()+ " falls to the ground in pain.",
          all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]) {
  case -10..25:
    at->do_damage((string)at->return_target_limb(), random(8)+1);
    break;
  case 26..40:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "stun A");
    break;
  case 41..53:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "stun B");
    do_critical(from, at, "impact A");
    break; 
  case 54..65:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "impact C");
    do_critical(from, at, "impact B");
    break;
  case 66..82:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "stun D");
    do_critical(from, at, "impact C");
    break;
  case 83..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+1));
    do_critical(from, at, "stun E");
    do_critical(from, at, "impact D");
    break;
  }
  remove();
  return;
}
 
