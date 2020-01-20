inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental barrier");
    set_property("skill","elementalism");
    set_property("casting time",15);
    set_property("base mp cost",33);
    set_property("dev cost",47);
    set_property("fast dev cost",142);
    set_property("spell level", 9);
    set_property("moon","warzau");
    set_property("caster message","You cast elemental barrier at $T.");
    set_property("target message","$C casts elemental barrier at you.");
    set_property("observer message","$C casts elemental barrier at $T.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", 11);
    set_property("stack key", "ele protection");
    set_property("stack num", 4);
    set_property("duration", 240);
    set_property("target type", "living");
    set_property("prereq", "elemental shield");
    return;
}

void info() {
message("help",
"This spell protects the target from a particular elemental damage.  "
"It is more powerful than 'elemental shield'.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

