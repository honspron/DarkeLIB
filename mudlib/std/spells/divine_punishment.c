inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name", "divine punishment");
    set_property("skill","prayer");
    set_property("casting time", 3);
    set_property("base mp cost", 55);
    set_property("dev cost", 83);
    set_property("fast dev cost", 195);
    set_property("spell level", 16);
    set_property("moon","warzau");
    set_property("caster message","You call for divine retribution upon $T. "
		                  "Your prayers are answered as a bolt of "
		                  "lightning shoots out of the sky and smites "
		                  "your foe!");
    set_property("target message","$C calls for divine retribution upon you! "
		                  "A bolt of lightning shoots out of the sky, "
		                  "smiting you! A voice booms in your head,\n"
		                  "REPENT YE SINNER!");
    set_property("observer message","$C prays for divine retribution. "
		                    "A bolt of lightning shoots out of the "
		                    "sky and smites $T!");
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("prereq", "holy strike");
    set_property("can resist", 2);
    set_property("spell type",({ "damage" }));
    set_property("must be present", 1);
    set_property("damage types", ([ "electricity" : 30, "holy" : 30 ]));
    set_property("damage multiplier", 7.5);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spells appeals to the heavens for punishment upon the paladin's " +
"enemies.\n",
this_player());
}

