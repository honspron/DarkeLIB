// Coder: %^GREEN%^%^BOLD%^nEv!N%^RESET%^
// Darkemud
// Cleric GM Weapon, Ang'rir
// 10/02/96

#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

// the amount of energy stored in the hammer, special abilities require the use
// of these power points
int POWER;

void init() {
	::init();
	add_action("hammer_talk", "say");
// special functions disabled
//	add_action("grasp_hammer", "grasp");
//	add_action("summon_winds", "spin");
}

void create() {
	::create();
	set_ac(15);
	set_name("ang'rir");
	set("id", ({ "hammer" }) );
	set("short", "a brilliant hammer");
	set("long",
		"Finely crafted and blessed with symbols of the Lord, this "
		"ancient artifact of power has been used by countless heroes "
		"and heroines before you.  It's name in an ancient tongue "
		"no longer spoken in the Shadowlands is Ang'rir.  The hammer "
		"senses your soul and glows softly at your touch."
	);
	set_type("blunt");
	set_quality(6);
	set_property("no add quality", 1);
	set_property("no decay", 1);
	set_material("metal/javednite");
	TO->set_decay_rate(TO->prop("hardness"));
	set_wc(30, "crushing");
	set_wc(15, "impact");
	set_wc(10, "holy");
	set_verb("pulverize");
	set_parry_bonus(5);
	set_property("hit bonus", 15);
	set_property("enchantment", 15);
	set_wield( (: call_other, this_object(), "make_me_gm" :) );
	set_unwield( (: call_other, this_object(), "remove_hammer" :) );
	set_hit( (: call_other, this_object(), "undead_destroy" :) );
	set_enh_critical(1);
	set_weight(250);
	set_value(0);
	set_property("flight duration", 180);
// set high so that I can test it out
	POWER = 0;
	call_out("power_fade", 60);
	return;
}

string query_short() {
	string str;
	str = ::query_short();
	switch(POWER) {
		case 0..10: str = str + "...it glows faintly"; 
			break;
		case 11..30: str = str + "...it glows with a dull light"; 
			break;
		case 31..60: str = str + "...it glows with a soft light"; 
			break; 
		case 61..100: str = str + "...it glows with a warm light"; 
			break;
		case 101..150: str = str + "...it glows with a bright light"; 
			break;
		case 151..210: str = str + "...it glows with an intense light";
			 break;
		case 211..300: str = str + "...it glows fiercely!"; 
			break;
		case 301..500: str = str + "...it glows with an eldrich "
			"light!"; break;
		case 501..1000: str = str + "...it glows with a blinding "
			"light!"; break;
		case 1001..10000: str = str + "...it glows with an unearthly "
			"light!"; break;
	}
	return str;
}

int query_always_keep() { return 1; }

// the power in the hammer fades at a rate of 5/minute
void power_fade() {
	POWER -= 1;
	if(POWER < 0) { POWER = 0; }
	call_out("power_fade", 60);
}

int make_me_gm() {
	object ob;
	
	seteuid(getuid());
	if(TP->query_cap_name() == "Nevin") { return 1; }
	if(!(TP->query_class() == "cleric")) {
		message("info", "%^RED%^%^BOLD%^Upon touching the holy weapon, a bolt of "
			"energy rips into your body throwing you "
			"into the air!%^RESET%^", TP);
		message("info", "%^RED%^%^BOLD%^As "+TPQCN+" tries to grab a brilliant "
			"hammer, a bolt of energy rips into "+TP->
			query_possessive()+" body!%^RESET%^", ENV(TP), ({TP}) );
		TP->add_hp( -(TP->query_hp()/2) );
		TP->set_paralyzed(60, "Your chest feels like it is on fire!  "
			"You struggle to stand upright but the pain is just "
			"too intense, you collapse back upon the ground.");
		return 0;
	}
	message("info", "The hammer glows brightly as you grab it for "
		"battle.  The hammer seems to change in size and balance as "
		"it fits perfectly into your grasp.  A faint voice in your "
		"head says, 'Greetings noble one, how may I serve you?'", 
		this_player());
	ob = new("/d/damned/guilds/cleric/cleric_obj");
	ob->make_me_master(this_player());
	return 1;
}

int remove_hammer() {
	message("info", "The hammer dims slightly as you unwield it.",
		this_player());
	return 1;
}

// hammer will smash through undead and chaotic-lords
// disabled the special crit stuff and weapon charging
int undead_destroy(object attacker) {
//	if(((string)attacker->query("race") == "undead") ||
//		(string)attacker->query_class() == "chaotic-lord") {
//		message("info", "%^CYAN%^%^BOLD%^"+TP->query_cap_name()+"'s hammer flares to "
//			"life upon striking such foul flesh!%^RESET%^", ENV(TP), ({TP}) );
//		message("info", "%^CYAN%^%^BOLD%^Your hammer flares to life upon striking "
//			"such foul flesh!%^RESET%^", TP);
//		if(random(2) == 0) {
//			message("info", "Ang'rir begins to glow...", TP);
//			message("info", TPQCN+"'s hammer begins to glow...", 
//				ENV(TP), ({TP}) );
//			POWER += 1;
//		}
//		set_enh_critical(2);
//		do_critical(this_player(), attacker, "holy C");
//		return ( random(10) + 5 );
//	}
	set_enh_critical(1);
	return 0;
}

// hammer will respond to the player's help inquiry
int hammer_talk(string str) {
	if(!str) { return 0; }
	if(str == "ang'rir, help") {
		message("info", "A soft voice in your mind tells you..."
			"Long have I awaited your coming.  May I serve you "
			"well.  I am Ang'rir.  I was forged in an age long "
			"ago.  Within me is the ability to grant to you "
			"various powers...these powers have been disabled "
			"temporarily.  ", TP);
//			"To gain the ability to fly, type: 'grasp hammer "
//			"tightly'.  "
//			"  To "
//			"summon a curtain of holiness type: 'swing hammer "
//			"above my head'.  Any undead or minion of Marghuul "
//			"who enters a room will suffer greatly.  "
//			"To create a whirlwind of holy energy type: 'spin "
//			"hammer quickly'.  Doing this will send waves of "
//			"holy energy flying about the room harming any "
//			"undead or minion of Marghuul foolish enough to "
//			"remain in the room with the cleric of light.",
//			TP);
		return 1;
	}
}

// function to grant flight to owner of hammer
int grasp_hammer(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you wish to grasp?\n");
		return 0;
	}
	if(POWER < 100) {
		message("info", "A soft voice informs you that it is not "
			"able to grant you flight at this time.", TP);
		return 1;
	}
	if(TP->query_flying()) {
		message("info", "A soft voice informs you that you are "
			"already flying.", TP);
		return 1;
	}
	if(str == "hammer tightly") {
		message("info", "Wings of gossamer form upon your back.", TP);
		message("info", "Gossamer wings of flight form upon the "
			"back of "+TPQCN+".", ENV(TP), ({TP}) );
		ob = new("/std/spells/shadows/lev_shadow");
		ob->start_shadow(TP, props["flight duration"], "Your gossamer "
			"wings fade into a sparkling cloud.");
		POWER -= 100;
		return 1;
	}
}

// function to summon winds of righteousness
int summon_winds(string str) {
	object *inv;
	int i;
	if(!str) {
		notify_fail("What do you wish to spin?\n");
		return 0;
	}
	if(POWER < 250) {
		message("info", "A soft voice informs you that it is not "
			"able to summon the winds of righteousness at this "
			"time", TP);
		return 1;
	}
	if(str == "hammer quickly") {
		message("info", "You spin the hammer above your head.  "
			"Swirling clouds of sparking light trail behind "
			"the hammer.  The gushing winds slam into everyone "
			"in the room!", TP);
		message("info", TPQCN+" spins "+TP->query_possessive()+
			" hammer above "+TP->query_possessive()+" head.  "
			"Gusting winds swirl around you!", ENV(TP), ({TP}) );
		inv = all_inventory(ENV(TP));
		i = sizeof(inv);
		while(i--) {
			if(living(inv[i])) {
				if( (inv[i]->query_class() == "chaotic-lord") ||
				    (inv[i]->query_race() == "undead") ) {
					do_critical(TP, inv[i], "holy E"); 
					do_critical(TP, inv[i], "holy D");
					do_critical(TP, inv[i], "holy C");
					do_critical(TP, inv[i], "holy B");
					do_critical(TP, inv[i], "holy A");
				}
			}
		}
		POWER -= 250;
		return 1;
	}
}

int query_power() { return POWER; }
