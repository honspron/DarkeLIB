inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","meteor storm");
    set_property("skill","conjuration");
    set_property("casting time",9);
    set_property("base mp cost",60);
    set_property("dev cost", 120);
    set_property("fast dev cost", 340);
    set_property("spell level", 22);
    set_property("moon","warzau");
    set_property("caster message","You cast a METEOR STORM.");
    set_property("target message","$C casts a METEOR STORM!");
    set_property("observer message","$C casts a METEOR STORM.");
    set_property("spell type",({ "area damage" }));
    set_property("must be present", 1);
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("damage types", ([ "fire" : 35, "fire #2" : 35, "fire #3" : 35 ]));
    set_property("damage multiplier", 6);
    set_property("combat spell", 1);
    set_property("no target", 1);
    set_property("prereq", "blizzard");
    return;
}

void info() {
message("help",
"This spell hurls several meteors at all enemies!",
this_player());
}
