inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","blizzard");
    set_property("skill","conjuration");
    set_property("casting time",6);
    set_property("base mp cost",42);
    set_property("dev cost", 90);
    set_property("fast dev cost", 250);
    set_property("spell level",16);
    set_property("moon","warzau");
    set_property("caster message","You cast a blizzard.");
    set_property("target message","$C casts a blizzard!");
    set_property("observer message","$C casts a blizzard.");
    set_property("spell type",({ "area damage" }));
    set_property("must be present", 1);
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("damage types", ([ "cold" : 25, "impaling" : 20, "cold #2" : 25 ]));
    set_property("damage multiplier", 3.5);
    set_property("combat spell", 1);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This spell conjures a blizzard of razor sharp ice shards to stike all enemies!",
this_player());
}

