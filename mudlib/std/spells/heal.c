inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","heal");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost",40);
    set_property("dev cost", 58);
    set_property("fast dev cost", 140);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast a healing spell upon $T.");
    set_property("target message","$C casts a healing spell upon you.");
    set_property("observer message","$C casts a healing spell upon $T.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "20D10");
    set_property("must be present",1);
    set_property("prereq", "cure critical wounds");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This is a very powerful healing spell, restoring even more hp than cure critical wounds.",
this_player());
}
