inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","hex");
    set_property("skill","necromancy");
    set_property("casting time",3);
    set_property("base mp cost",15);
    set_property("dev cost", 10);
    set_property("fast dev cost", 32);
    set_property("spell level", 1);
    set_property("moon","ankh");
    set_property("caster message","You cast a hex on $T.");
    set_property("target message","$C casts a hex on you.");
    set_property("observer message","$C casts a hex on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "-1D6");
    set_property("stats", ({ "strength", "intelligence", "dexterity" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 240);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell gives a general short-term penalty in stats to the "
"target.  Hexes are stackable.",
this_player());
}







