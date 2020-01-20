inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","chaos storm");
    set_property("skill","chaos magic");
    set_property("must be present", 1);
    set_property("casting time",4);
    set_property("base mp cost",45);
    set_property("dev cost", 67);
    set_property("fast dev cost", 170);
    set_property("spell level", 23);
    set_property("moon","warzau");
    set_property("caster message","You cast a chaos storm.");
    set_property("target message","$C casts a chaos storm!");
    set_property("observer message","$C casts a chaos storm.");
    set_property("spell type",({ "area damage" }));
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("damage types", ([ "disruption" : 30 ]));
    set_property("damage multiplier", 9);
    set_property("combat spell", 1);
    set_property("no target", 1);
    set_property("prereq", "chaos ball");
    return;
}

void info() {
message("help",
"This spell hurls a chaos storm at the target, damaging all targets not "
"in your party!",
this_player());
}

