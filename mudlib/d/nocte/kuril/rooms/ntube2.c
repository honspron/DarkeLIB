// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from Khojem's ravine code

#include <std.h>
#include "nevin.h"
inherit ROOM;

void init() {
	::init();
	if(!(int)this_player()->query_flying()) { call_out("drop_me", 1, TP); }
	add_action("fly_down", "down");
	add_action("fly_up", "up");
}

void create() {
	::create();
	set_property("light", 2);
	set_property("night light", -3);
	set_property("indoors", 0);
	set("short", "A runed covered tube");
	set("long",
		"Near the top of the tube, you can are unable to see to the "
		"bottom of the tube from here.  Something appears to be "
		"moving around down there...something large."
	);
	set_items( ([
		"tubes": "The tube walls are covered with runes.",
		"runes": (: call_other, this_object(), "look_rune" :),
		"walls": "They offer no purchase at all!  The runes which "
			"cover them are obviously magical in nature."
	]) );
	set_exits( ([
		"up": ROOMS+"ntube1",
		"down": ROOMS+"ntube3"
	]) );
}

void drop_me(object player) {
	message("info", "With nothing to hold onto you fall into the depths "
		"below!\n", player);
	message("info", player->query_cap_name()+" flails around like mad, "
		"but falls into the depths below.", ENV(player), ({player}) );
	message("info", player->query_cap_name()+" falls from above!",
		ROOMS+"ntube3", ({player}) );
	player->move_player(ROOMS+"ntube3");
}

void look_rune() {
	if((string)this_player()->query_class() == "enchanter") {
		write("You are unable to make out all of the runes but you "
			"are able to recognize the symbols of flight and "
			"levitation.");
		return;
	}
	else {
		write("You are unable to understand any of the runes on the "
			"walls of the tube.");
		return;
	}
}

int fly_up() {
	if(!TP->query_flying()) {
		write("You try to flap your arms around but you can not fly!");
		say(TPQCN+" tries to take flight by flapping "+
			TP->query_possessive()+" arms "
			"around...strange.");
		return 1;
	}
	if(this_player()->query_flying()) {
		write("You fly up the tube.");
		tell_room("/wizards/nevin/kuril/tubes/ntube1",
			this_player()->query_cap_name() + "flies up from " +
				"the depths below.");
	}
}

int fly_down() {
	if(!TP->query_flying()) {
		return 1;
	}
	if(this_player()->query_flying()) {
		write("You fly down into the depths.");
		tell_room("/wizards/nevin/kuril/tubes/ntube3",
			this_player()->query_cap_name() + " flies down "
				"from above.");
	}
}
