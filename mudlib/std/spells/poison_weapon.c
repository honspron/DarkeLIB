inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","poison weapon");
    set_property("skill","magery");
    set_property("casting time",8);
    set_property("base mp cost",25);
    set_property("dev cost", 6);
    set_property("fast dev cost", 15);
    set_property("spell level", 1);
    set_property("moon","luna");
    set_property("caster message","You cast poison weapon at $T.");
    set_property("target message","");
    set_property("observer message","$C casts poison weapon at $T.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("duration", "see below");
    return;
}

void info() {
message("help",
"This spell, when cast at a weapon, imbues it with a magical "
"poison, much the same as applying weapon poison.  The poison fades "
"after a few hits, like normal poison, but until then, it will stay on "
"permanently.  The power determines the strength of the poison.\n"
"Syntax: cast *3 poison weapon at <weapon>",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  if(!at->is_weapon()) {
    message("info", "You must cast this spell at a weapon.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You accidentally poison yuorself!", caster);
    caster->add_poisoning(30*power);
    remove();
    return;
  }
  message("info", "A glowing fluid appears on the weapon.", caster);
  at->add_poisoning((18+random(30)) * power);
  remove();
  return;
}
