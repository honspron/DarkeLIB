inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","wind of death");
    set_property("skill","necromancy");
    set_property("casting time",4);
    set_property("base mp cost",30);
    set_property("dev cost",97);
    set_property("fast dev cost", 223);
    set_property("spell level",18);
    set_property("moon","warzau");
    set_property("caster message","You cast death wind at $T,");
    set_property("target message","$C casts death wind at you!");
    set_property("observer message","$C casts death wind at $T");
    set_property("spell type",({ "damage" }));
    set_property("damage types",([ "cold":10, "cold #2":15,
          "cold #3":20, "cold #4":60, "cold #5":20, "cold #6":10]));
    set_property("damage multiplier", 2);
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "cold blast");
    return;
}

void info() {
message("help",
 "This spell fires 4 gusts of freezing wind at the casters enemy.",
this_player());
}

