inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy word");
    set_property("skill","prayer");
    set_property("casting time",1);
    set_property("base mp cost",10);
    set_property("dev cost",6);
    set_property("fast dev cost",18);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("damage multiplier", 2);
    set_property("caster message","You say a holy word at $T!");
    set_property("target message","$C says a holy word at you!");
    set_property("observer message","$C says a holy word at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "holy" : 12 ]));
    set_property("combat spell", 1);
    set_property("must be present", 1);
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This is a minor damage spell which has holy effects, particularly against undead "
"creatures.",
this_player());
}

