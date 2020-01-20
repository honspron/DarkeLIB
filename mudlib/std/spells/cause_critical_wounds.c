inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cause critical wounds");
    set_property("skill","prayer");
    set_property("casting time",8);
    set_property("base mp cost",32);
    set_property("dev cost", 30);
    set_property("fast dev cost", 95);
    set_property("spell level", 8);
    set_property("moon","warzau");
    set_property("caster message","You cover $T with festering wounds!");
    set_property("target message","$C covers you with festering wounds!");
    set_property("observer message","$C covers $T with festering wounds!");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "-6D12");
    set_property("must be present",1);
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    set_property("target type", "living");
    set_property("combat spell", 1);
    set_property("prereq", "cause serious wounds");
    return;
}

void info() {
message("help",
"This spell severely harms the target, but cannot kill him/her.",
this_player());
}
