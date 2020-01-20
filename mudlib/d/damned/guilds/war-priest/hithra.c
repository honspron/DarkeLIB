// Coder: %^GREEN%^%^BOLD%^nEv!N%^RESET%^
// Darkemud
// Priests of K'thach GM Weapon, Hithra
// 10/04/96

#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

int POWER;

void init() {
	::init();
	add_action("hammer_talk", "say");
//	add_action("lightning_power", "summon");
//	add_action("swing_sword", "swing");
//	add_action("ball_lightning", "create");
}

void create() {
	::create();
	set_ac(20);
	set_name("hithra");
	set("id", ({ "hithra", "sword", "massive sword" }) );
	set("short", "a massive sword");
	set("long",
		"The air seems to shimmer about this blade.  Cold to the "
		"touch, this mighty weapon can reek destruction upon "
		"the foes of its wielder.  Upon the blade is the word "
		"'Hithra', although you do not recognize the language that "
		"it is written in, you are able to understand the writing." 
	);
	set_type("two handed blade");
	set_quality(6);
	set_property("no add quality", 1);
	set_property("no decay", 1);
	set_material("metal/elrodnite");
	TO->set_decay_rate(TO->prop("hardness"));
	set_wc(30, "cutting");
	set_wc(15, "cold");
	set_wc(15, "vacuum");
	set_verb("massacre");
	set_parry_bonus(5);
	set_property("hit bonus", 20);
	set_property("enchantment", 15);
	set_wield( (: call_other, this_object(), "make_me_gm" :) );
	set_hit( (: call_other, this_object(), "special_hit" :) );
	set_enh_critical(1);
	set_weight(300);
	set_value(0);
// set high so that I can test it out
	POWER = 0;
	set_property("electricity duration", 300);
	call_out("power_fade", 60);
	return;
}

// special short messages, alter to fit the weapon
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
		case 1001..100000: str = str + "...it glows with an unearthly "
			"light!"; break;
	}
	return str;
}

int query_always_keep() { return 1; }

// the power in the hammer fades at a rate of 1/minute
void power_fade() {
	POWER -= 1;
	if(POWER < 0) { POWER = 0; }
	call_out("power_fade", 60);
}

// wield function, checks the class of the would be wielder
int make_me_gm() {
	object ob;
	
	seteuid(getuid());
	if(TP->query_cap_name() == "Nevin") { return 1; }
	if(!(TP->query_class() == "war-priest")) {
		message("info", "%^RED%^%^BOLD%^A bolt of energy blasts "
			"into your chest!", TP);
		message("info", "%^RED%^%^BOLD%^A bolt of energy blasts "
			"into "+TPQCN+"'s chest throwing "+TP->
			query_objective()+" back several feet!", ENV(TP),
			({TP}) );
		TP->add_hp( -(TP->query_hp() * 2/3) );
		TP->set_paralyzed(60, "Your chest feels like it is on fire!  "
			"You struggle to stand upright but the pain is just "
			"too intense, you collapse back upon the ground.");
		return 0;
	}
	message("info", "The sound of thunder echoes in the distance as "
		"you ready the blade for battle.  A deep resounding voice "
		"fills the air...", TP);
	message("info", "The sound of thunder echoes in the distance as "+
		TPQCN+" grabs a massive sword for battle.  A deep resounding "
		"voice fills the air...", ENV(TP), ({TP}) );
	message("info", "Greetings "+TPQCN+", I am Hithra, first Priest of "
		"K'thach.  For centuries I have served the faithful of "
		"K'thach in the form of this blade.  May you wield me "
		"well, may your battles be glorious!", ENV(TP) );
	message("info", "Simply type: 'say hithra, help' for assistance on "
		"how to use this weapon.", TP);
	ob = new("/d/damned/guilds/war-priest/war-priest_obj");
	ob->make_me_master(this_player());
	return 1;
}

int special_hit(object attacker) {
//	if(random(5)) {
//		message("info", "%^CYAN%^%^BOLD%^"+TP->query_cap_name()+"'s "
//			"sword emits a ear deafening thunder clap!", ENV(TP),
//			({TP}) );
//		message("info", "%^CYAN%^%^BOLD%^Your sword emits an "
//			"ear deafening thunder clap!", TP);
//		message("info", "Hithra begins to glow...", TP);
//		message("info", TPQCN+"'s sword begins to glow...", 
//			ENV(TP), ({TP}) );
//		POWER += 1;
//		return ( random(5) + 3 );
//	}
	set_enh_critical(1);
	return 0;
}

// sword will respond to the player's help inquiry
int hammer_talk(string str) {
	if(!str) { return 0; }
	if(str == "hithra, help") {
		message("info", "A booming voice tells you..."
			"Greetings "+TPQCN+", to aid you in your cause "
			"I have certain special abilties which you can "
			"invoke.  In order to power my special abilities "
			"you must first prove yourself in battle.  Doing so "
			"will put energy into me.  You may release this "
			"energy with the following commands:\n\n"
			"SPECIAL FUNCTIONS CURRENTLY DISABLED (Nevin)", TP);
//			"<summon grace of k'thach>        by summoning the "
//			"grace of K'thach, electricity will flow into your "
//			"blade\n"
//			"<swing sword in full circle>	  conjuring a "
//			"lightning storm will hit everyone in the room with "
//			"bolts of lightning.\n"
//			"<create ball lightning>	  globes of pure "
//			"electricity, ball lightning, will form before you.  "
//			"To send them unerringly upon their way, use the "
//			"the command <send ball at <target name> >.\n"
		return 1;
	}
}

// function to add electricity criticals
int lightning_power(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you wish to summon?\n");
		return 0;
	}
	if(POWER < 100) {
		message("info", "A booming voice tells you that it is not "
			"able to summon the grace of K'thach at this time",
			TP);
		return 1;
	}
	if(str == "grace of K'thach") {
		message("info", "Electricity begins to dance along your "
			"blade.", TP);
		ob = new("/std/spells/shadows/weapon_shadow");
		ob->set_extra_wc( ([ "electricity": 20 ]) );
		ob->set_auto_crits( ([ "electricity A": 15 ]) );
		ob->start_shadow(TO, props["electricity duration"],
			"%^CYAN%^The electricity fades from your blade.");
		return 1;
	}
}

// function to create a lightning storm
int swing_sword(string str) {
	object *inv;
	int i;
	if(!str) {
		notify_fail("What do you wish to swing?\n");
		return 0;
	}
	if(POWER < 200) {
		message("info", "A booming voice tells you that it is not "
			"able to create a lightning storm at this time.", TP);
		return 1;
	}
	if(str == "sword in full circle") {
		message("info", "You swing the sword around and around!  "
			"Electrical energy crackles along the blade until..."
			"Shhhrrraccckkzzz!  The energy flies from the blade "
			"hitting everyone in the room!", TP);
		message("info", TPQCN+" swings "+TP->query_possessive()+
			" sword around and around!  Tendrils of lightning "
			"lance off from the end of the blade scorching "
			"everyone in the room with its deadly touch!",
			ENV(TP), ({TP}) );
		inv = all_inventory(ENV(TP));
		i = sizeof(inv);
		while(i--) {
			if(living(inv[i])) {
				if(!(inv[i] == TP)) {
				do_critical(TP, inv[i], "electricity E");
				do_critical(TP, inv[i], "electricity D");
				do_critical(TP, inv[i], "electricity C");
				}
			}
		}
		POWER -= 200;
		return 1;
	}
}

// function to create ball lightning
int ball_lightning(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you wish to create?\n");
		return 0;
	}
	if(POWER < 500) {
		message("info", "A booming voice tells you that it is not "
			"able to create ball lightning at this time.", TP);
		return 1;
	}
	if(str == "ball lightning") {
		message("info", "You raise Hithra toward the sky...in "
			"response a bolt of lightning arcs down from the sky! "
			" Upon opening your eyes, you find glowing balls "
			"of pure energy surrounding you.", TP);
		message("info", TPQCN+" raises "+TP->query_possessive()+
			" to the sky...suddenly a bolt of lightning arcs down "
			"from the sky!  After clearing away the after "
			"images in your eyes, you see that there are glowing "
			"balls of energy surround "+TPQCN+".", ENV(TP), ({TP}));
		POWER -= 500;
		ob = new("/d/damned/guilds/cleric/ball_lightning");
		ob->power_up((int)TP->query_level() + random(5));
		ob->move(ENV(TP));
		return 1;
	}
}

int query_power() { return POWER; }
