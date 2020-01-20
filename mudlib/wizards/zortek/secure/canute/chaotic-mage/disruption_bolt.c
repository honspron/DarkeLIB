inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","disruption bolt");
    set_property("skill","chaos magic");
     set_property("casting time", 2);
    set_property("base mp cost",10);
    set_property("dev cost", 11);
    set_property("fast dev cost", 26);
    set_property("spell level", 5);
    set_property("moon","warzau");
    set_property("save mod", "dexterity");
    set_property("can save", 2);
    set_property("caster message","You cast a bolt of disruption at $T.");
    set_property("target message","$C casts a bolt of disruption at you!");
    set_property("observer message","$C casts a bolt of disruption at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "disruption" : 12 ]));
    set_property("damage multiplier", 3);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell hurls a bolt of disruption at the target.",
this_player());
}

