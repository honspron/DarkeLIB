inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","cause light wounds");
    set_property("skill","prayer");
    set_property("base mp cost",7);
    set_property("casting time",4);
    set_property("dev cost", 5);
    set_property("fast dev cost", 15);
    set_property("spell level", 2);
    set_property("moon","warzau");
    set_property("caster message","You cause minor wounds to appear on $T.");
    set_property("target message","$C causes minor wounds to appear on you.");
    set_property("observer message","$C causes minor wounds to appear on $T.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "-6D4");
    set_property("must be present",1);
    set_property("target type", "living");
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    set_property("combat spell",1);
    return;
}

void info() {
message("help",
"This spell causes minor wounds to form on the target, but it will not kill him or her.",
this_player());
}
