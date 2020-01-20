inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","heal");
    set_property("skill","prayer");
    set_property("casting time",18);
    set_property("base mp cost",75);
    set_property("dev cost", 70);
    set_property("fast dev cost", 190);
    set_property("spell level", 15);
    set_property("moon","ankh");
    set_property("caster message","You cast a mass healing spell upon $T.");
    set_property("target message","$C casts a mass healing spell upon you.");
    set_property("observer message","$C casts a mass healing spell upon $T.");
    set_property("spell type",({ "area healing" }));
    set_property("heal dice", "10D8");
    set_property("must be present",1);
    set_property("prereq", "heal");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell heals all present in the room...including monsters.  "
"The strength of the spell is slightly less than a heal spell.",
this_player());
}
