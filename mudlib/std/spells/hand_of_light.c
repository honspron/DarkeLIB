inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","hand of light");
    set_property("skill", "prayer");
    set_property("casting time",4);
    set_property("base mp cost",32);
    set_property("dev cost", 21);
    set_property("fast dev cost", 60);
    set_property("spell level", 4);
    set_property("moon","warzau");
    set_property("save mod", "wisdom");
    set_property("can save", 1);
    set_property("caster message","You call the Hand of Light to strike $T.");
    set_property("target message","$C casts the Hand of Light at you!");
    set_property("observer message","$C casts the Hand of Light at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "holy" : 18 ]));
    set_property("damage multiplier",4.2);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell hurls holy energy at the target, a more powerful version of holy word.",
this_player());
}

