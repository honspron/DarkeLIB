inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","divine might");
    set_property("skill","body alteration");
    set_property("casting time",6);
    set_property("base mp cost",15);
    set_property("dev cost", 7);
    set_property("fast dev cost", 17);
    set_property("spell level", 2);
    set_property("moon","luna");
    set_property("caster message","You cast divine might on $T.");
    set_property("target message","$C casts divine might on you.");
    set_property("observer message","$C casts divine might on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "2D8");
    set_property("stats", ({ "strength" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 480);
    set_property("stack key", "dmight");
    set_property("stack num", 3);
    return;
}

void info() {
message("help",
"This spell gives the recipient a temporary increase in strength.",
this_player());
}

