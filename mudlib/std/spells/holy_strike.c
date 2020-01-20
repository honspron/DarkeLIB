inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy strike");
    set_property("skill","prayer");
    set_property("casting time",2);
    set_property("base mp cost",24);
    set_property("dev cost", 57);
    set_property("fast dev cost", 122);
    set_property("spell level", 11);
    set_property("moon","warzau");
    set_property("save mod", "wisdom");
    set_property("can save", 1);
    set_property("caster message","You call a holy strike upon $T.");
    set_property("target message","$C casts a holy strike at you!");
    set_property("observer message","$C casts a holy strike at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "holy" : 30 ]));
    set_property("damage multiplier",6);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "holy word");
    return;
}

void info() {
message("help",
"This spell hurls holy energy at the target, a more powerful version of holy word.",
this_player());
}
