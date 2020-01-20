inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","distance healing");
    set_property("skill","prayer");
    set_property("casting time",18);
    set_property("base mp cost",55);
    set_property("dev cost", 68);
    set_property("fast dev cost", 185);
    set_property("spell level", 12);
    set_property("moon","ankh");
    set_property("caster message","You cast a healing spell upon $T.");
    set_property("target message","$C casts a healing spell upon you.");
    set_property("observer message","$C casts a healing spell upon $T.");
    set_property("target observer message", "$T is healed by $C.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "20D6");
    set_property("target type", "player");
    return;
}

void info() {
message("help",
"This spell is a slightly less potent version of the 'heal' spell, except "
"that the recipient may be anywhere on the mud.  The recipient must be a "
"player.",
this_player());
}
