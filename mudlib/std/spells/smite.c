inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name", "smite");

    set_property("skill","prayer");

    set_property("casting time", 3);

    set_property("base mp cost", 32);

    set_property("dev cost", 70);

    set_property("fast dev cost", 163);

    set_property("spell level", 13);

    set_property("moon","warzau");

    set_property("caster message","You pray for God to smite $T! ");

    set_property("target message","$C prayed for God to smite you! ");

    set_property("observer message","$C prayed for God to smite $T! ");

    set_property("save mod", "wisdom");

    set_property("can resist", 2);

    set_property("spell type",({ "damage" }));

    set_property("must be present", 1);

    set_property("damage types", ([ "fire": 10, "impact" : 10, "holy" : 20 ]));

    set_property("damage multiplier", 3);

    set_property("combat spell", 1);

    set_property("target type", "living");

    set_property("prereq", "harm");
    return;

}



void info() {

message("help",

"This prayer is a request for Him to smite your foe.\n",

this_player());

}



