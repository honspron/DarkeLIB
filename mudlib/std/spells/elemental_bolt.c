inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental bolt");
    set_property("skill","elementalism");
    set_property("casting time", 2);
    set_property("base mp cost",18);
    set_property("dev cost",20);
    set_property("fast dev cost",61);
    set_property("spell level", 3);
    set_property("moon","warzau");
    set_property("caster message","You cast an elemental bolt at $T!");
    set_property("target message","$C casts an elemental bolt at you!");
    set_property("observer message","$C casts an elemental bolt at $T.");
    set_property("spell type",({ "damage" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele damage", 29);
    set_property("damage multiplier", 4.3);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "lesser elemental bolt");
    return;
}

void info() {
message("help",
"This spell fires an elemental bolt at a single target.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

