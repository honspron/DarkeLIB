inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","vacuum bolt");
    set_property("skill","conjuration");
    set_property("casting time",3);
    set_property("base mp cost",41);
    set_property("dev cost", 61);
    set_property("fast dev cost", 156);
    set_property("spell level", 11);
    set_property("moon","warzau");
    set_property("caster message","You cast a vacuum bolt at $T.");
    set_property("target message","$C casts a vacuum bolt at you!");
    set_property("observer message","$C casts at vacuum bolt at $T.");
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("can resist", 2);
    set_property("spell type",({ "damage" }));
    set_property("must be present", 1);
    set_property("damage types", ([ "vacuum" : 45 ]));
    set_property("damage multiplier", 11);
    set_property("combat spell", 1);
    set_property("prereq", "lightning bolt");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell hurls a bolt of pure vacuum at the target!",
this_player());
}

