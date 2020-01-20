inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name", "hammer of god");
    set_property("skill","prayer");
    set_property("casting time", 6);
    set_property("base mp cost", 66);
    set_property("dev cost", 83);
    set_property("fast dev cost", 213);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You drop the HAMMER on $T! ");
    set_property("target message","$C drops the HAMMER on you! ");
    set_property("observer message","$C drops the HAMMER on $T! ");
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("can resist", 2);
    set_property("spell type",({ "damage" }));
    set_property("must be present", 1);
    set_property("damage types", ([ "impact" : 45, "holy" : 30 ]));
    set_property("damage multiplier", 8);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spells calls upon heavenly force to the smash your foes!\n",
this_player());
}

