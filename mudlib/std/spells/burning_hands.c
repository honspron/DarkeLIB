inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","burning hands");
    set_property("skill","conjuration");
    set_property("casting time",1);
    set_property("base mp cost",11);
    set_property("dev cost", 6);
    set_property("fast dev cost", 15);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast burning hands at $T.");
    set_property("target message","Flames shoot out of $C's hands at you!");
    set_property("observer message","Flames shoot from $C's hands at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "fire" : 10, "fire #2" : 10 ]));
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("can save", 2);
    set_property("damage multiplier", 2);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell allows the caster to shoot jets of flame at the target from his/her hands.",
this_player());
}

