inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cure light wounds");
    set_property("skill","prayer");
    set_property("casting time",1);
    set_property("base mp cost",7);
    set_property("dev cost", 5);
    set_property("fast dev cost", 15);
    set_property("spell level", 1);
    set_property("moon","ankh");
    set_property("caster message","You lightly cure some of $T's wounds.");
    set_property("target message","$C lightly cures some of your wounds.");
    set_property("observer message","$C lightly cures some of $T's wounds.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "6D4");
    set_property("must be present",1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell resores some lost hp to the target.",
this_player());
}
