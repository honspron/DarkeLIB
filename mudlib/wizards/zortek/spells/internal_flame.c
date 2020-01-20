inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","internal flame");
    set_property("skill","conjuration");
    set_property("casting time",4);
    set_property("base mp cost",44);
    set_property("dev cost", 85);
    set_property("fast dev cost", 240);
    set_property("spell level", 18);
    set_property("moon","warzau");
    set_property("caster message","You cast a internal flame at $T.");
    set_property("target message","$C casts a internal flame at you!");
    set_property("observer message","$C casts a internal flame at $T.");
    set_property("spell type",({ "damage" }));
    set_property("must be present", 1);
    set_property("can resist", 2);
    set_property("save mod", "constitution");
    set_property("damage types", ([ "fire":150]));
    set_property("damage multiplier", 20);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell does A LOT of damage to a single target by creating a flame "
"inside the target!",
this_player());
}

