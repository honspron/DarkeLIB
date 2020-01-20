inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","lesser elemental bolt");
    set_property("skill","elementalism");
    set_property("casting time",1);
    set_property("base mp cost",9);
    set_property("dev cost",7);
    set_property("fast dev cost",20);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast a lesser elemental bolt at $T!");
    set_property("target message","$C casts a lesser elemental bolt at you!");
    set_property("observer message","$C casts a lesser elemental bolt at $T.");
    set_property("spell type",({ "damage" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele damage", 12);
    set_property("damage multiplier", 2);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell fires a minor elemental bolt at a single target.  This is an "
"elemental spell (see 'help spellsys'), and must be used with an elemental lore "
"skill.",
this_player());
}

