inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","faerie fire");
    set_property("skill","illusionism");
    set_property("casting time",4);
    set_property("base mp cost",11);
    set_property("dev cost", 5);
    set_property("fast dev cost", 13);
    set_property("spell level", 2);
    set_property("stack key", "faerie fire");
    set_property("stack num", 2);
    set_property("moon","luna");
    set_property("caster message","You summon a glowing aura about $T.");
    set_property("target message","$C summons a glowing aura about you.");
    set_property("observer message","$C summons a glowing aura about $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("duration", 160);
    return;
}

void info() {
message("help",
"This spell summons a luminescent aura around a creature, lighting up the "
"room and making it easier to hit.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  ob = new("/std/spells/shadows/ff_shadow");
  ob->set_light((power > 4)?4:power);
  ob->start_shadow(at, props["duration"],
	           "The faerie fire aura about you fades.");
  return;
}
