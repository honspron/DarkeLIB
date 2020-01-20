inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","chaos ball");
    set_property("skill","chaos magic");
    set_property("casting time", 2);
    set_property("base mp cost",20);
    set_property("dev cost", 30);
    set_property("fast dev cost", 80);
    set_property("spell level", 12);
    set_property("moon","warzau");
    set_property("save mod", "dexterity");
    set_property("can save", 2);
    set_property("caster message","You cast a ball of chaos at $T.");
    set_property("target message","$C casts a ball of chaos at you!");
    set_property("observer message","$C casts a ball of chaos at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "disruption" : 25 ]));
    set_property("damage multiplier", 5);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "disruption bolt");
    return;
}

void info() {
message("help",
"This spell hurls a ball of chaos at the target.",
this_player());
}

