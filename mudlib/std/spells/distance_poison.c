#include "/adm/include/spell.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","distance poison");
    set_property("skill","body alteration");
    set_property("casting time",12);
    set_property("base mp cost",41);
    set_property("dev cost", 61);
    set_property("fast dev cost", 190);
    set_property("spell level",18);
    set_property("moon","warzau");
    set_property("save mod", "constitution");
    set_property("can save", 1);
    set_property("caster message","You cast distance poison.");
    set_property("target message","");
    set_property("observer message","$C utters some magical incantations.");
    set_property("spell type",({ }));
    set_property("combat spell", 1);
    set_property("no target", 1);
    set_property("prereq", "scry");
    return;
}

void info() {
message("help",
"This spell can be used to poison targets at a distance.  A successful scry is required first.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int pois, i;
  
  if(!(at = (object)caster->query("scry"))) {
    message("info", "You must scry the target first ('help spell scry').",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(time() > (int)caster->query("scry time")) {
    message("info", "Your scry has expired.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    at = caster;
    message("info", "You direct the spell at yourself!", caster);
    message("info", CQN+" accidentally directs the spell at "+
      objective(caster)+"self!", EC, ({ caster }));
  }
  pois = 0;
  for(i=1;i <= 10;i++) pois += 1+random(12);
  pois *= power;
  at->add_poisoning(pois);
  message("info", "%^GREEN%^Odd, you feel terribly sick...", at);
  remove();
  return;
}

  
