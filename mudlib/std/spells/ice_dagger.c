inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","ice dagger");
    set_property("skill","conjuration");
    set_property("casting time", 2);
    set_property("base mp cost",25);
    set_property("dev cost", 23);
    set_property("fast dev cost", 65);
    set_property("spell level", 4);
    set_property("moon","warzau");
    set_property("caster message","You cast ice daggers at $T!");
    set_property("target message","$C casts ice daggers upon you!");
    set_property("observer message","$C casts ice daggers at $T!");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "impaling" : 17, "cold" : 26 ]));
    set_property("damage multiplier", 2.8);
    set_property("can save", 1);
    set_property("save mod", "dexterity");
    set_property("must be present",1);
    set_property("combat spell",1);
    return;
}

void info() {
message("help",
"This spell casts ice daggers at the foe, shredding him most heinously.",
this_player());
}
