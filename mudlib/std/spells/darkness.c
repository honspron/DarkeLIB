inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","darkness");
    set_property("skill","illusionism");
    set_property("casting time",5);
    set_property("base mp cost",15);
    set_property("dev cost", 8);
    set_property("fast dev cost", 22);
    set_property("spell level", 2);
    set_property("moon","luna");
    set_property("caster message","You summon a globe of darkness.");
    set_property("target message","");
    set_property("observer message","$C summons a globe of darkness.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 160);
    return;
}

void info() {
message("help",
"This spell summons a globe of darkness that can blind most creatures.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  ob = new("/std/spells/shadows/light_shad");
 ob->set_light(flag?2:-5);
  ob->start_shadow(caster, props["duration"],
	           "A darkness spell expires.");
  return;
}
