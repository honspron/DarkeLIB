/* hermit */

#include <std.h>
inherit MONSTER;

void create() {
	::create();
	set_name("hermit");
	set("id", ({"hermit", "The hermit", "truelan", "Truelan"}) );
	set_level(20);
	set_max_hp(1000);
	set_hp(1000);
	set("short", "hermit");
	set("long",
		"You see a wise looking old man standing before you.  Deep in "
		"his eyes you see knowledge far beyond mortal man.");
	set("race", "human");
	set_gender("male");
	set_money("gold", 100+(random(20)));
	set_body_type("human");
	set_overall_ac(25);
	set_skill("conjuration", 85);
	set_skill("illusionism", 85);
	set_skill("magery", 85);
	set_languages( ({"common","dwarvish","elvish"}) );
	set_combat_chance(80);
	add_spell("fireball", "$A");
	set_spell_level("fireball", 6);
	add_spell("ice dagger", "$A");
	set_spell_level("fireball", 6);
	add_spell("lightning bolt", "$A");
	set_spell_level("lightning bolt", 6);
	set_emotes(5, ({
		"The hermit eyes you expectantly.",
		"The hermit yawns.",
		"The hermit ambles about the hut.",
		"The hermit stirs the coals in the fire."
			}), 0);
	set_achats(20, ({
		"The hermit yells, \"You wretched mortal, thou shall die!\"",
		"The hermit growls, \"Is that the best you can do?!?\"",
		"The hermit states, \"Why do I waste my time with you?\"",
		"The hermit snarls, \"Go back to your momma, weakling!"",
			}) );
	new("/wizards/glitch/swamp/items/staff")->move(this_object());
	force_me("wield staff in left hand and right hand");
	force_me("use concentrate");
}
