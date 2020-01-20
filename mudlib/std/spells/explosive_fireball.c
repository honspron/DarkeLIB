inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","explosive fireball");
    set_property("skill","conjuration");
    set_property("must be present", 1);
    set_property("casting time",8);
    set_property("base mp cost",20);
    set_property("dev cost", 67);
    set_property("fast dev cost", 170);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You cast an explosive fireball.");
    set_property("target message","$C casts an explosive fireball!");
    set_property("observer message","$C casts an exploseive fireball.");
    set_property("spell type",({ "area damage" }));
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("damage types", ([ "fire" : 30 ]));
    set_property("damage multiplier", 4);
    set_property("combat spell", 1);
    set_property("no target", 1);
    set_property("prereq", "fireball");
    return;
}

void info() {
message("help",
"This spell hurls a fireball at the target, damaging all targets not "
"in your party!",
this_player());
}

