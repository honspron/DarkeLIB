// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from Khojem's ravine code

#include <std.h>
#include <nevin.h>
inherit ROOM;

void init() {
	::init();
	if(!this_player()->query_flying()) { call_out("drop_me", 1, TP); }
	add_action("fly_down", "down");
	add_action("fly_up", "up");
}

void create() {
	::create();
	set_property("light", 1);
	set_property("night light", -3);
	set_property("indoors", 0);
	set("short", "A runed covered tube");
	set("long",
		"Almost at the bottom of the tube, you can see water below "
		"you.  The tube walls surround you with their wierd runes. "
	);
	set_items( ([
		"water": "Hope you know how to swim.",
		"runes": (: call_other, this_object(), "look_rune" :),
		"walls": "They offer no purchase at all!  The runes which "
			"cover them are obviously magical in nature."
	]) );
	set_exits( ([
		"up": ROOMS+"ntube2",
		"down": ROOMS+"ntube4"
	]) );
}

void drop_me(object player) {
	message("info", "With nothing to hold onto you fall into the depths "
		"below!\n", player);
	message("info", player->query_cap_name()+" flails around like mad, "
		"but falls into the depths below.", ENV(player), ({player}) );
	message("info", player->query_cap_name()+" falls from above!  "
		"Hmmm, not a very graceful landing there.\n",
		ROOMS+"ntube4", ({player}) );
	player->move_player(ROOMS+"ntube4");
	player->add_hp(-100);
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
		write("You try and flap your arms around but you just can "
			"not fly");
		say(TPQCN+" tries to take flight by flapping "+
			TP->query_possessive()+" arms around...strange.");
		return 1;
	}
	if(this_player()->query_flying()) {
		write("You fly up the tube.");
		tell_room("/wizards/nevin/kuril/tubes/ntube2",
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
		tell_room("/wizards/nevin/kuril/tubes/ntube4",
			this_player()->query_cap_name() + " flies down "
				"from above.");
	}
}
