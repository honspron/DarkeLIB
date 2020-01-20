inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cure critical wounds");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost",32);
    set_property("dev cost", 30);
    set_property("fast dev cost", 95);
    set_property("spell level", 7);
    set_property("moon","ankh");
    set_property("caster message","You almost totally cure $T of all wounds.");
    set_property("target message","$C cures most all of your wounds.");
    set_property("observer message","$C cures most all of $T's wounds.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "6D12");
    set_property("must be present",1);
    set_property("prereq", "cure serious wounds");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell restores a great deal of hp to the target.",
this_player());
}
