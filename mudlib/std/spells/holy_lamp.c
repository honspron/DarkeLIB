// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Holy Lamp: Priests of Akhamshish
// Modified from holy_light.c
// Light Spell:		casting time: 7
//	        	base mp cost: 12
//              	dev cost: 4
//              	fast dev cost: 11

#include <security.h>
inherit "/std/spells/spell";

void create() {
	::create();
    	set_property("name","holy lamp");
    	set_property("skill","prayer to akhamshish");
    	set_property("casting time", 9);
    	set_property("base mp cost", 14);
    	set_property("dev cost", 5);
    	set_property("fast dev cost", 13);
    	set_property("spell level", 1);
    	set_property("moon","luna");
    	set_property("caster message",
		"%^YELLOW%^%^BOLD%^You offer a prayer to Akhamshish to guide "
		"your way.  A glowing lamp swirls into a solid form before you.");
    	set_property("target message","");
    	set_property("observer message",
		"%^YELLOW%^%^BOLD%^$C offers a prayer to Akhamshish as a lamp "
		"begins to glow.");
    	set_property("spell type",({ }));
    	set_property("no target", 1);
    	set_property("duration", 180);
    	return;
}

void info() {
	string *spells;
	spells = TP->query_all_spells();
	if(member_array("holy lamp", spells) != -1) {
		message("help",
			"Prerequisite Spell: Ceremony of Purification\n\n"
			"\tThis spell causes a lamp to glow with the "
			"blessed light of Akhamshish.  May the light of "
			"Akhamshish guide your path.  At high power levels "
			"the caster may feel the direct warmth of "
			"Akhamshish.\n\n"
			"Usage: cast *<pow> holy lamp\n"
			"Example: cast *1 holy lamp\n", TP);
	}
	else {
		message("help", "It is believed that the Priests of "
			"Akhamshish can form magical lamps from the light "
			"of their lord", TP);
	}
}

void spell_func(object caster, object at, int power, string args, int flag) {
	object ob;
	if(caster->query_spell_level("ceremony of purification") < 
		( (props["extra power"])?(power-props["extra power"]):power) ) {
		message("info", "But wait!  You loose control of the magic!  "
			"Shafts of light slam into your eyes!  You are "
			"blinded!", caster);
		ob = new("/std/spells/shadows/blind_shadow");
		ob->start_shadow(caster);
		call_out("expire blind", (180 + 30*power), caster, ob);
		remove();
		return;
	}
	if(flag) {
		message("info", "You are blinded by the holy light of "
			"Akhamshish!", caster);
		message("info", caster->query_cap_name()+" is blinded by the "
			"holy light of Akhamshish!", ENV(caster), ({caster}) );
		ob = new("/std/spells/shadows/blind_shadow");
		ob->start_shadow(caster);
		call_out("expire blind", props["duration"], caster, ob);
		remove();
		return;
	}
	ob = new("/wizards/nevin/guilds/ak/obj/glamp");
	ob->set_up(props["duration"], power);
	ob->move(caster);
	if(power > 5) {
		switch(random(3)) {
			case 0: message("info", "You are bathed in the holy "
				"light of Akhamshish, you feel purified and "
				"cleansed.  Blessed be Akhamshish!", caster);
				break;
			case 1: message("info", "You feel the warmth of "
				"Akhamshish.", caster); break;
			case 2: message("info", "Holy light bathes your face. "
				"You see Akhamshish in a vision.  He instructs "
				"you to prepare the world for his arrival.",
				caster); break;
		}
	}
  	return;
}
