inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","greater elemental storm");
    set_property("skill","elementalism");
    set_property("casting time",6);
    set_property("base mp cost",60);
    set_property("dev cost",78);
    set_property("fast dev cost",230);
    set_property("spell level", 19);
    set_property("moon","warzau");
    set_property("caster message","You cast a greater elemental storm!");
    set_property("target message","$C casts a greater elemental storm!");
    set_property("observer message","$C casts a greater elemental storm.");
    set_property("spell type",({ "area damage", "area damage" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele damage", 42);
    set_property("damage multiplier", 18);
    set_property("combat spell", 1);
    set_property("no target", 1);
    set_property("prereq", "elemental storm");
    return;
}

void info() {
message("help",
"This spell, when cast, will strike all enemies with a force "
"slightly greater than 2 greater elemental bolts.",
this_player());
}

