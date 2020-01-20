inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cold blast");
    set_property("skill","necromancy");
    set_property("casting time",2);
    set_property("base mp cost",20);
    set_property("dev cost", 38);
    set_property("fast dev cost", 92);
    set_property("spell level", 7);
    set_property("moon","warzau");
    set_property("save mod", "constitution");
    set_property("can save", 2);
    set_property("caster message","You cast a cold blast at $T.");
    set_property("target message","$C casts a cold blast at you!");
    set_property("observer message","$C casts a cold blast at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "cold" : 28 ]));
    set_property("damage multiplier",6);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "freeze skin");
    return;
}

void info() {
message("help",
"This spell hurls a blast of cold at the target.",
this_player());
}

