inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental shield");
    set_property("skill","elementalism");
    set_property("casting time",12);
    set_property("base mp cost", 12);
    set_property("dev cost",7);
    set_property("fast dev cost",22);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast elemental shield at $T.");
    set_property("target message","$C casts elemental shield at you.");
    set_property("observer message","$C casts elemental shield at $T.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", 6);
    set_property("stack key", "ele protection");
    set_property("stack num", 4);
    set_property("duration", 60);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell protects the target from a particular elemental damage.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

