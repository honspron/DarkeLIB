#include <spell.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","indomitable spirit");
    set_property("skill","body alteration");
    set_property("casting time",5);
    set_property("base mp cost",36);
    set_property("dev cost", 5);
    set_property("fast dev cost", 15);
    set_property("spell level", 11);
    set_property("moon","ankh");
    set_property("caster message","You cast indomitable spirit at $T.");
    set_property("target message","$C casts indomitable spirit upon you!");
    set_property("observer message","$C casts indomitable spirit at $T.");
    set_property("spell type",({ }));
    set_property("duration",40);
    set_property("must be present", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell makes the target immune to stunning for a short time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  if(flag) {
    message("info", "You accidentally stun "+TQN+"!", caster);
    message("info", CQN+" accidentally stuns "+TQN+"!", EC, ({ caster, at }));
    message("info", CQN+" accidentally stuns you!", at);
    at->set("no stun", 0);
    at->set_paralyzed(4*power);
    remove();
    return;
  }
  if(at->query("no stun")) {
    message("info", TQN+" is already resistant to stunning.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->set("no stun", 1);
  message("info", "You are now resistant to stunning.", at);
  call_out("remove_will", props["duration"], at);
  return;
}

void remove_will(object who) {
  if(!who) {
    remove();
    return;
  }
  message("info", "%^RED%^%^BOLD%^Indomitable Spirit wears off..", who);
  who->set("no stun", 0);
  remove();
  return;
}
