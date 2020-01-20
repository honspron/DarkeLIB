#include "/adm/include/spell.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","body disruption");
    set_property("skill","body alteration");
    set_property("casting time",5);
    set_property("base mp cost",25);
    set_property("dev cost", 26);
    set_property("fast dev cost", 74);
    set_property("spell level", 5);
    set_property("moon","warzau");
    set_property("save mod", "constitiution");
    set_property("can resist", 1);
    set_property("caster message","You cast body disruption at $T.");
    set_property("target message","$C casts body disruption at you!");
    set_property("observer message","$C casts body disruption at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "disurption" : 37 ]));
    set_property("damage multiplier", 5);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell casts a disrupting attack at the victim, damaging and "
"poisoning him/her/it.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int pois, i;
  
  if(flag) {
    at = caster;
    message("info", "You direct the spell at yourself!", caster);
    message("info", CQN+" accidentally directs the spell at "+
      objective(caster)+"self!", EC, ({ caster }));
  }
  pois = 0;
  for(i=1;i <= 10;i++) pois += 1+random(10);
  pois *= power;
  at->add_poisoning(pois);
  ::spell_func(caster, at, power, args, 0);
  remove();
  return;
}

  
