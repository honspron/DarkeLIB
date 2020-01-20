inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","garguth's grasping hand");
    set_property("skill", "energy manipulation");
    set_property("casting time",2);
    set_property("base mp cost",15);
    set_property("dev cost",6);
    set_property("fast dev cost",15);
    set_property("spell level", 5);
    set_property("moon","warzau");
    set_property("caster message","You cast Garguth's grasping hand at $T.");
    set_property("target message","A big hand appears out of thin air ready to cursh you!");
    set_property("observer message","$C concentrates intently, and a big, grasping hand appears above $T...");
    set_property("combat spell", 1);
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("target type", "living");
    set_property("combat spell", 1);
    set_property("must be present", 1);
    set_property("spell type",({ "damage" }));
    set_property("damage multiplier", 4);
    set_property("damage types", ([ "crushing" : 16 ]));
    set_property("prereq", "garguth's open palm");
    return;
}

void info() {
message("help",
"This spell causes the magical palm of Garguth the giant to "
"appear above the target and crush him/her by squeezing.",
this_player());
}

