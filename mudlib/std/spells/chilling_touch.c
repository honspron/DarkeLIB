inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","chilling touch");
    set_property("skill","necromancy");
    set_property("casting time",1);
    set_property("base mp cost",10);
    set_property("dev cost", 6);
    set_property("fast dev cost", 15);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast chilling touch at $T.");
    set_property("target message","You are chilled by $C's touch!");
    set_property("observer message","$C's touch chills $T");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "cold" : 10 ]));
    set_property("can resist", 2);
    set_property("save mod", "constitution");
    set_property("can save", 2);
   set_property("damage multiplier", 2);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell allows the caster to attack the target with a chilling touch.",
this_player());
}

