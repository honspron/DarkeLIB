inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","bolt of righteousness");
    set_property("skill","prayer");
    set_property("casting time",3);
    set_property("base mp cost",30);
    set_property("dev cost", 92);
    set_property("fast dev cost", 249);
    set_property("spell level", 18);
    set_property("moon","warzau");
    set_property("caster message","You hurl Pope Fred's Bolt of Righteousness at $T!");
    set_property("target message","HALLELUJAH!  $C hurls Pope Fred's Bolt of Righteousness at you!");
    set_property("observer message","HALLELUJAH!  $C hurls Pope Fred's Bolt of Righteousness at $T.");
    set_property("spell type",({ "damage" }));
    set_property("must be present", 1);
    set_property("damage types", ([ "holy" : 50 ]));
    set_property("damage multiplier", 35);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "smite");
    return;
}

void info() {
message("help",
"This is a truly impressive spell.  Invented by Pope Fred, It hurls a bolt "
"of pure holiness at the opponent.  It has been known to have interesting side-"
"effects, such as summoning angelic beings to the site of combat...",
this_player());
}

