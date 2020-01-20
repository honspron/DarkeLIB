// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Tssn'ri Egg for the Chaotic-Lord GM Weapon, Chemoch
// 	- egg is dropped upon the ground upon creation, whenever a player
// 	  enters a room with a tssn'ri egg in it, he may be forced to take
//	  up the egg and eat it.  Later, a Tssn'ri will erupt from the chest
//        of the player causing significant damage and them immediately
//	  attacking the player. 
//	- eggs will crumble away after a period of time--they are not
//	  meant to survive upon the plane of the Shadowlands
// 10/02/96

#include <std.h>

inherit "/std/food";

void init() {
	::init();
	add_action("eat_egg", "eat");
	if(wizardp(TP)) { return; }
	if(TP->query_class() == "chaotic-lord") { return; }
	if(living(TP)) {
		if(((int)TP->query_stats("wisdom") + (int)TP->
			query_stats("intelligence")) > random(300) ) {return;}
		message("info", "You pick up the large greyish egg.  It "
			"seems to grow warmer at your touch...\n", TP);
		message("info", TPQCN+" picks up a large greyish egg.\n",
			ENV(TP), ({TP}) );
		message("info", "Upon grabbing the egg you have this "
			"absolutely uncontrolable urge to eat it!  Your "
			"arm seems to move on its own volition as the "
			"egg approaches your mouth.  The egg begins to "
			"beat like a large grey heart.  You swallow the "
			"egg whole!  It begins sliding down your "
			"throat but you can tell that it is not falling..."
			"it is wiggling down into your body...\n", TP);
		message("info", TPQCN+" eats a large greyish egg.\n", ENV(TP),
			({TP}) );
		call_other("/wizards/nevin/workrooms/tssnri_pool", 
			"create_spawn", TP);
		message("info", "The egg feels as if it is forcing its own "
			"way down your throat...", TP);
		TO->remove();
	}
	return;
}

void create() {
	::create();
	set_name("tssn'ri egg");
	set_my_mess("The egg feels as if it is forcing its own way down your "
		"throat...");
	set_id( ({ "egg", "tssn'ri egg" }) );
	set_short("a large greyish egg");
	set_strength(0);
	set_long("Coloured a dull grey, this large egg makes you almost "
		"puke just to see the way throbs.  Something living is "
		"currently resting inside it...waiting...");
	set_weight(30);
	set_value(0);
	call_out("destroy_me", 300);
}

int eat_egg(string str) {
	if(!str) { return 0; }
	if(str == "egg") {
		call_other("/wizards/nevin/workrooms/tssnri_pool",
                        "create_spawn", TP);
		message("info", "The egg feels as it it is forcing its own "
			"way down your throat...", TP);
		TO->remove();
		return 1;
	}
}

void destroy_me() { 
	message("info", "A greyish egg crumbles to dust...", ENV(TO));
	TO->remove();
}
