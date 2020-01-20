inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","fire protection");
    set_property("skill","magery");
    set_property("casting time",8);
    set_property("base mp cost",10);
    set_property("dev cost", 35);
    set_property("fast dev cost", 90);
    set_property("moon","ankh");
    set_property("spell level",8);
    set_property("duration",200);
    set_property("caster message","You cast fire protection on $T.");
    set_property("target message","$C casts fire protection on you.");
    set_property("observer message","$C casts fire protection on $T.");
    set_property("spell type",({ "protection" }));
    set_property("protection types",([ "fire" : 10 ]));
    set_property("must be present",1);
    return;
}

void info() {
message("help",
"This spell casts a mild protective aura around the recipient, protecting "
"him or her from fire-based attacks.",
this_player());
}
