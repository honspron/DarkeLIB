inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental bane");
    set_property("skill","elementalism");
    set_property("casting time",8);
    set_property("base mp cost",56);
    set_property("dev cost",76);
    set_property("fast dev cost",205);
    set_property("spell level", 15);
    set_property("moon","warzau");
    set_property("caster message","You cast elemental curse at $T.");
    set_property("target message","$C casts elemental curse at you.");
    set_property("observer message","$C casts elemental curse at $T.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", -7);
    set_property("stack key", "ele curse");
    set_property("stack num", 2);
    set_property("duration", 180);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "elemental curse");
    return;
}

void info() {
message("help",
"This spell is a more powerful version of the spell 'elemental curse'.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

