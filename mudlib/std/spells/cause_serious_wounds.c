inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cause serious wounds");
    set_property("skill","prayer");
    set_property("casting time",6);
    set_property("base mp cost",19);
    set_property("dev cost", 20);
    set_property("fast dev cost", 64);
    set_property("spell level", 5);
    set_property("moon","warzau");
    set_property("caster message","You severely wound $T.");
    set_property("target message","$C severely wounds you!");
    set_property("observer message","$C severely wounds $T.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "-6D8");
    set_property("must be present",1);
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    set_property("target type", "living");
    set_property("combat spell", 1);
    set_property("prereq", "holy word");
    return;
}

void info() {
message("help",
"This spell heavily wounds the target, but cannot kill him/her.",
this_player());
}
