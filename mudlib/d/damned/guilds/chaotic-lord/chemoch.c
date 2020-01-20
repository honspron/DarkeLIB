// Coder: %^GREEN%^%^BOLD%^nEv!N%^RESET%^
// Darkemud
// Chaotic-Lord GM Weapon, Chemoch
// 10/02/96

// NEED: /d/damned/guilds/chaotic-lord/breeding_pit.c 		(object)
//       - feed_me_seymour(), increases duration of pit
//	 /d/damned/guilds/chaotic-lord/tssnri_egg.c		(object)
//	 /wizards/nevin/workrooms/tssnri_pool.c			(object)
//	 /d/damned/guilds/chaotic-lord/tssnri.c			(object)
//	 /d/damned/guilds/chaotic-lord/nihil.c			(object)

#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

int POWER, TENDRILS;

void init() {
	::init();
	add_action("look_tendrils", "look");
	add_action("blade_talk", "say");
	add_action("form_egg", "form");
	add_action("feed_pit", "feed");
	add_action("breeding_pit", "create");
}

void create() {
	::create();
	set_ac(20);
	set_name("blade");
	set("id", ({ "chemoch", "blade", "gray sword", "gray blade", "sword" }) );
	set("short", "a gray bladed sword");
	set("long",
		"Forged in the fires of the lower planes, this sword, Chemoch, "
		"was given to Ther'kal by Marghuul himself.  Quenched in the "
		"blood of a hundred paladins of Celeborn, this blade has an "
		"inner life that seeks only to destroy, to kill, and to cause "
		"suffering where and whenever it can."
	);
	set_type("blade");
	set_quality(6);
	set_property("no add quality", 1);
	set_property("no decay", 1);
	set_material("an otherworldly material");
	set_decay_rate(2000);
	set_wc(30, "cutting");
	set_wc(15, "impaling");
	set_wc(10, "infernal");
	set_wc(10, "paralysis");
	set_verb("mutilate");
	set_parry_bonus(5);
	set_property("hit bonus", 15);
	set_property("enchantment", 15);
	set_wield( (: call_other, this_object(), "make_me_gm" :) );
	set_unwield( (: call_other, this_object(), "remove_blade" :) );
	set_hit( (: call_other, this_object(), "kill_them_all" :) );
	set_enh_critical(1);
	set_weight(200);
	set_value(100000);
// set high so that I can test it out
	POWER = 10000;
	TENDRILS = 0;
	set_property("blind duration", 30);
	call_out("power_fade", 60);
	return;
}

string query_short() {
	string str;
	str = ::query_short();
	switch(POWER) {
		case 0..10: str = str + "...it pulsates faintly"; 
			break;
		case 11..30: str = str + "...it pulsates very softly"; 
			break;
		case 31..60: str = str + "...it pulsates softly"; 
			break; 
		case 61..100: str = str + "...it pulsates with an inner life"; 
			break;
		case 101..150: str = str + "...it pulsates disgustingly"; 
			break;
		case 151..210: str = str + "...it pulsates with a sickening "
			"sound"; break;
		case 211..300: str = str + "...it pulsates with a putrid glow";
			 break;
		case 301..500: str = str + "...it pulsates with hypnotic "
			"regularity"; break;
		case 501..1000: str = str + "...it pulsates with an unholy "
			"light!"; break;
		case 1001..10000: str = str + "...it pulses with an "
			"otherworldly light!"; break;
	}
	return str;
}

int query_always_keep() { return 1; }

void power_fade() {
	POWER -= 1;
	if(POWER < 0) { POWER = 0; }
	call_out("power_fade", 60);
}

int make_me_gm() {
	object ob;
	
	seteuid(getuid());
	if(TP->query_cap_name() == "Nevin") { return 1; }
	if(!(TP->query_class() == "chaotic-lord")) {
		message("info", "%^RED%^%^BOLD%^You grab the weapon, but "
			"an overriding urge to shoove the weapon into you "
			"gut takes over!  You slam the blade into your "
			"stomach and quickly drop the blade.%^RESET%^", TP);
		message("info", "%^RED%^%^BOLD%^As "+TPQCN+" tries to grab a "
			"grey bladed sword...but suddenly slams the blade "
			"deep into "+TP->query_possessive()+" own gullet!  "
			"Blood pours out of the wound as "+TPQCN+" releases "
			"the blade.%^RESET%^", ENV(TP), ({TP}) );
		TP->add_hp( -(TP->query_hp() * (9/10)) );
		return 0;
	}
	message("info", "The blade shifts and wiggles in your hand as you "
		"grab it for battle.  A sibilant voice hisses in your "
		"mind, 'HooOwWwww MaaY i seErVee yOOuuu MMmaAassSterr?'", TP);
		call_out("blade_connect", 3, TP);
	ob = new("/d/damned/guilds/chaotic-lord/chaotic-lord_obj");
	ob->make_me_master(TP);
	return 1;
}

void blade_connect(object who) {
	message("info", "Suddenly long slender tendrils snake out from the "
		"hilt of the sword!  They eat their way into your arm!  "
		"You can feel the tendrils probing their way under your skin "
		"and toward your shoulder...the pain is becoming almost too "
		"much to bear!!!  Suddenly, when you feel as if you may "
		"pass out, the pain receeds and you are left with a numb "
		"feeling in your arm.", who);
	who->add_hp( -(who->query_hp()/10) );
	TENDRILS = 1;
	return;
}

int remove_blade() {
	message("info", "You feel very reluctant to release the blade.  A "
		"sick feeling forms in your stomach but you manage to hold "
		"the rising bile down.  The tendrils that had formed a "
		"bond with your body slip out from beneath your skin and "
		"disappear into the handle of the blade.", TP);
	TENDRILS = 0;
	return 1;
}

int kill_them_all(object attacker) {
	if(random(5) == 0) {
	message("info", "%^RED%^%^BOLD%^"+TP->query_cap_name()+"'s "
		"blade flashes to life!%^RESET%^", ENV(TP), ({TP}) );
	message("info", "%^RED%^%^BOLD%^Your blade flashes to "
		"life!%^RESET%^", TP);
		message("info", "Chemoch begins to pulsate...", TP);
		message("info", TP->query_cap_name()+"'s blade begins "
			"to pulsate...", ENV(TP), ({TP}) );
		POWER += 1;
	}
	return;
}

// player gets to see what the sick tendrils are doing
int look_tendrils(string str) {
	if(!str) { return 0; }
	if(!TENDRILS) { 
		message("info", "You do not see any tendrils.", TP);
		return 0;
	}
	message("info", "The tendrils have wound their way under your skin.  "
		"Somehow they have formed some type of mental and physical "
		"bond with your body.", TP);
	return 1;
}

// blade will respond to the player's help inquiry
int blade_talk(string str) {
	if(!str) { return 0; }
	if(str == "chemoch, help") {
		message("info", "A sibilant voice purrs in the back of "
			"your mind...  'Greetings maaasssterrr.  Together "
			"we can perform the following feats:'\n\n"
			"<form tssn'ri egg>      creates a tssn'ri egg\n"
			"<feed breeding pit>     extends the duration of a "
			"breeding pit\n"
			"<create breeding pit>   creates a breeding pit, from "
			"the pit will emerge creatures of darkness to serve "
			"you\n"
			"'Each ability requires a certain amount of energy.  "
			"Energy which only you can provide me by slaying "
			"your enemies.'", TP);
		return 1;
	}
}

// function to form a tssn'ri egg
int form_egg(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you wish to form?\n");
		return 0;
	}
	if(POWER < 75) {
		message("info", "A sibilant voice echoes in your head that "
			"you are unable to form a tssn'ri egg at this time",
			TP);
		return 1;
	}
	if(str == "tssn'ri egg") {
		message("info", "You prick your finger upon the tip of the "
			"blade.  A strand of some type of ooze begins to "
			"form on the end of the blade.  The ooze forms into "
			"a ball and drops to the ground before you.", TP);
		ob = new("/d/damned/guilds/chaotic-lord/tssnri_egg");
		ob->move(ENV(TP));
		POWER -= 75;
		return 1;
	}
}

// function to feed a breeding pit
int feed_pit(string str) {
	object pit;
	if(!str) {
		notify_fail("What do you wish to feed?\n");
		return 0;
	}
	if(POWER < 100) {
		message("info", "A sibliant voice whispers to you in the "
			"back of your mind telling you that you do not "
			"have the strength to feed a breeding pit at this "
			"time", TP);
		return 1;
	}
	if(str == "breeding pit") {
		if(!(pit = present("breeding pit", ENV(TP)))) {
			message("info", "There is no breeding pit here for "
				"you to feed.", TP);
			return 1;
		}
		message("info", "You hold your blade over the breeding pit.  "
			"A thin line of fluid runs down into the breeding "
			"pit.  The darkness within seems to rotate faster.",
			TP);
		message("info", TPQCN+" holds a sword over a breeding pit.  "
			"A thin line of fluid runs down into the breeding "
			"pit.  The darkness within seems to rotate faster.",
			ENV(TP), ({TP}) );
		pit->feed_me_seymour();
		POWER -= 100;
		return 1;
	}
}

// function to create a breeding pit
int breeding_pit(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you wish to create?\n");
		return 0;
	}
	if(POWER < 500) {
		message("info", "A sibilant voice in the back of your mind "
			"tells you that you do not have the strength to "
			"create a breeding pit at this time.", TP);
		return 1;
	}
	if(str == "breeding pit") {
		message("info", "You turn the blade upside-down and draw "
			"out a circle upon the ground.  Slicing a deep "
			"cut into your arm, you let your life blood drip "
			"into the center of the circle.  Almost instantly "
			"the blood thins and spreads to fill the circle.  "
			"A darkness begins to swirl within the circle while "
			"forms can be seen rising and falling within the "
			"newly formed breeding pit.", TP);
		message("info", TPQCN+" draws a circle upon the ground with "+
			TP->query_possessive()+" blade.  Slicing "+TP->
			query_possessive()+" arm open, blood is allowed to "
			"drip into the circle.  Almost immediately the "
			"blood thins out to cover the entire circle.  Darkness "
			"begins to swirl within the newly formed breeding "
			"pit.  Foul forms can be seen rising and falling "
			"within the swirling darkness.", ENV(TP), ({TP}) );
		TP->add_hp( -(TP->query_hp()/10) );
		seteuid(getuid());
		ob = new("/d/damned/guilds/chaotic-lord/breeding_pit");
		ob->set_up(TP->query_cap_name());
		ob->move(ENV(TP));
		POWER -= 500;
		write_file("/wizards/nevin/logs/chemoch.log", TPQCN+" created "
			"a breeding pit at "+ctime(time())+".\n");
		return 1;
	}
}

int query_power() { return POWER; }
