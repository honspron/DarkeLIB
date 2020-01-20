// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Lamp of Night: Priests of Akhamshish
// Modified from holy_light.c

#include <security.h>
inherit "/std/spells/spell";

void create() {
	::create();
    	set_property("name","lamp of night");
    	set_property("skill","prayer to akhamshish");
    	set_property("casting time", 7);
    	set_property("base mp cost", 35);
    	set_property("dev cost", 26);
    	set_property("fast dev cost", 75);
    	set_property("spell level", 5);
    	set_property("moon","luna");
    	set_property("caster message",
		"%^YELLOW%^%^BOLD%^You offer a prayer to Akhamshish.  In "
		"response, a lamp of darkness forms for you.");
    	set_property("target message","");
    	set_property("observer message",
		"%^YELLOW%^%^BOLD%^$C offers a prayer to Akhamshish.  Shadows "
		"seem to drip off the $C's hands.  The shadows merge to form "
		"a lamp of pure darkness.");
    	set_property("spell type",({ }));
    	set_property("no target", 1);
    	set_property("duration", 180);
    	return;
}

void info() {
	string *spells;
	spells = TP->query_all_spells();
	if(member_array("lamp of night", spells) != -1) {
		message("help",
			"Prerequisite Spell: Ceremony of Purification\n\n"
			"\tThis spell causes a lamp of utter darkness to "
			"come into being.  The darkness emitted by the "
			"lamp will aid you in your quest to do the bidding "
			"of Akhamshish.  At high power levels the darkness "
			"may form a cloak of obscurement around you.\n\n"
			"Usage: cast *<pow> lamp of night\n"
			"Example: cast *1 lamp of night\n", TP);
	}
	else {
		message("help", "It is believed that the Priests of "
			"Akhamshish can form magical lamps that can turn day "
			"into night.", TP);
	}
}

void spell_func(object caster, object at, int power, string args, int flag) {
	object ob;
	if(caster->query_spell_level("ceremony of purification") < 
		( (props["extra power"])?(power-props["extra power"]):power) ) {
		message("info", "But wait!  You are not experienced enough to "
			"control such powers!  Tendrils of darkness reach for "
			"your heart, you feel faint and pass out from the "
			"chill.", caster);
		caster->set_paralyzed(20 * power, "Your heart is still "
			"fluttering from the intense chill!");
		remove();
		return;
	}
	if(flag) {
		message("info", "Darkness swirls about you masking your sight!",
			caster);
		message("info", caster->query_cap_name()+" is surrounded by "
			"a cloak of darkness.  "+caster->query_subjective()+
			"seems to be blinded!", ENV(caster), ({caster}) );
		ob = new("/std/spells/shadows/blind_shadow");
		ob->start_shadow(caster);
		call_out("expire blind", props["duration"], caster, ob);
		remove();
		return;
	}
	ob = new("/wizards/nevin/guilds/ak/obj/dlamp");
	ob->set_up(props["duration"], power);
	ob->move(caster);
	if(power > 5) {
		if(random(10) == 0) {
			message("info", "A cloak of darkness swirls about you, "
				"you seem meld into the darkness.", caster); 
			ob = new("/std/spells/shadows/blur_shadow");
			ob->set_penalty(10);
			ob->start_shadow(caster, 60, "The cloak of darkness "
				"around you dissipates away.");
		}
	}
  	return;
}
