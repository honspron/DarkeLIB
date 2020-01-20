inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cure serious wounds");
    set_property("skill","prayer");
    set_property("casting time",3);
    set_property("base mp cost",20);
    set_property("dev cost", 20);
    set_property("fast dev cost", 64);
    set_property("spell level", 4);
    set_property("moon","ankh");
    set_property("caster message","You cure several of $T's wounds.");
    set_property("target message","$C cures several of your wounds.");
    set_property("observer message","$C cures several of $T's wounds.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "6D8");
    set_property("must be present",1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell restores some lost hp to the target.",
this_player());
}
