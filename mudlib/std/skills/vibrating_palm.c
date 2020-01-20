#include "/adm/include/clock.h"
inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(21);
    set_fast_dev_cost(48);
    set_property("target type", "living");
    set_property("must be present",1);
}

void info() {
message("help",
"This skill may be used against enemies in combat.  If you have an empty "+
"hand, you may strike your target with an attack that sends shocks through."+
"their body.  Sometimes it is enough to kill the target."
"  You may only use this skill once every fifteen min.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int flag, i;
  string *limbs,race;
  flag = ((int)from->query_level()) * 2;
  if((time() -(int)from->query_list_use("vibrating palm")) <((HOUR/4)-flag))
    {
    message("info", "You are too tired to use this skill yet."
        , from);
    return;
  }
  flag = 0;
  limbs = from->query_limbs();
  i = sizeof(limbs);
  while(i--) {
    if( (object)from->query_weapon(limbs[i]) ||
       (member_array("shield", (string *)from->query_armour(limbs[i])) > -1))
      flag++;
  }
  if((race != "ent" && flag > 1) || flag > 3) {
    message("my_action", "You do not have a free hand to strike with!",
from);
    remove(); 
    return;
  }
  from->set_last_use("vibrating palm");
  at->kill_ob(from, 0);
  props["skill level"] -= random(100);
  if((int)props["skill level"] < -10) {
    message("my_combat", "You attempt to strike "+
            (string)at->query_cap_name()+ " but miss miserably.",
            from);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to strike you with "+possessive(from)+
            " palm but misses.", at);
    message("other_combat", (string)from->query_cap_name() +
            " attempts to strike "+
            (string)at->query_cap_name()+ " with "+
            possessive(from)+ " palm but misses.",
            all_inventory(environment(from)),
            ({ from, at }) );
    remove();
    return;
  }
  message("my_combat", "You strike "+ 
          (string)at->query_cap_name()+ " with your palm shocking "+
          "them.",
          from);
  message("other_combat", (string)from->query_cap_name() +
          " strikes you with a fierce blow from " +possessive(from)+
          " palm.", at);
  message("other_combat", (string)from->query_cap_name() +
          " delivers a nasty strike to "+
          (string)at->query_cap_name()+ " with "+
          possessive(from)+ " palm.",
          all_inventory(environment(from)),
          ({ from, at }) );
  switch(props["skill level"]) {
  case -10..5:
    at->do_damage((string)at->return_target_limb(), random(15)+15);
    break;
  case 6..20:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+13));
    do_critical(from, at, "strike A");
    break;
  case 21..33:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+10));
    do_critical(from, at, "strike B");
    break;
  case 34..55:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+9));
    do_critical(from, at, "strike C");
    break;
  case 56..84:
    at->do_damage((string)at->return_target_limb(), 2 * (random(6)+8));
    do_critical(from, at, "strike D");
    break;
  case 85..10000:
    at->do_damage((string)at->return_target_limb(), 2 * (random(5)+8));
    do_critical(from, at, "strike E");
    break;
  }
  remove();   
  return;
}
