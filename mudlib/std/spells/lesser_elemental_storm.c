inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","lesser elemental storm");
    set_property("skill","elementalism");
    set_property("casting time",4);
    set_property("base mp cost",25);
    set_property("dev cost",37);
    set_property("fast dev cost",108);
    set_property("spell level", 7);
    set_property("moon","warzau");
    set_property("caster message","You cast a lesser elemental storm!");
    set_property("target message","$C casts a lesser elemental storm!");
    set_property("observer message","$C casts a lesser elemental storm.");
    set_property("spell type",({ "area damage" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele damage", 15);
    set_property("damage multiplier", 5);
    set_property("combat spell", 1);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This spell, when cast, will strike all enemies with a force "
"slightly greater than 2 lesser elemental bolts.",
this_player());
}

