inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental aegis");
    set_property("skill","elementalism");
    set_property("casting time",19);
    set_property("base mp cost", 55);
    set_property("dev cost",85);
    set_property("fast dev cost",265);
    set_property("spell level", 16);
    set_property("moon","warzau");
    set_property("caster message","You cast elemental aegis at $T.");
    set_property("target message","$C casts elemental aegis at you.");
    set_property("observer message","$C casts elemental aegis at $T.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", 17);
    set_property("stack key", "ele protection");
    set_property("stack num", 4);
    set_property("duration", 240);
    set_property("target type", "living");
    set_property("prereq", "elemental barrier");
    return;
}

void info() {
message("help",
"This spell protects the target from a particular elemental damage.  "
"It is more powerful than 'elemental barrier'.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

