inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","greater elemental bolt");
    set_property("skill","elementalism");
    set_property("casting time",3);
    set_property("base mp cost",34);
    set_property("dev cost",51);
    set_property("fast dev cost",153);
    set_property("spell level", 9);
    set_property("moon","warzau");
    set_property("caster message","You cast a greater elemental bolt at $T!");
    set_property("target message","$C casts a greater elemental bolt at you!");
    set_property("observer message","$C casts a greater elemental bolt at $T.");
    set_property("spell type",({ "damage" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele damage", 45);
    set_property("damage multiplier", 8);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "elemental bolt");
    return;
}

void info() {
message("help",
"This spell fires a major elemental bolt at a single target.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

