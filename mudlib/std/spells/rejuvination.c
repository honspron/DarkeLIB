inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","rejuvination");
    set_property("skill","woodland lore");
    set_property("casting time",1);
    set_property("base mp cost",7);
    set_property("dev cost", 5);
    set_property("fast dev cost", 15);
    set_property("spell level", 1);
    set_property("moon","ankh");
    set_property("caster message","You rejuvinate $T.");
    set_property("target message","$C rejuvinates you.");
    set_property("observer message","$C rejuvinates $T.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "7D4");
    set_property("must be present",1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell resores some lost hp to the target.",
this_player());
}
