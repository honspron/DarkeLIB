inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental curse");
    set_property("skill","elementalism");
    set_property("casting time",8);
    set_property("base mp cost",31);
    set_property("dev cost",31);
    set_property("fast dev cost",91);
    set_property("spell level", 6);
    set_property("moon","warzau");
    set_property("caster message","You cast elemental curse at $T.");
    set_property("target message","$C casts elemental curse at you.");
    set_property("observer message","$C casts elemental curse at $T.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", -4);
    set_property("stack key", "ele curse");
    set_property("stack num", 2);
    set_property("duration", 120);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell makes the target more vulnerable to a particular elemental damage.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

