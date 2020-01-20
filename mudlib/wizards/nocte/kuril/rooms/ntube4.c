// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from Khojem's ravine code

#include <std.h>
#include <nevin.h>
inherit ROOM;

void init() {
	::init();
	add_action("fly_up", "up");
	if(TP->chk_my_mob()) { 
		add_action("no_exit", "north");
		add_action("no_exit", "south");
	}
}

void reset() {
	::reset();
	if(!present("zombie")) {
		new(MON+"ku_zombie")->move(TO);
		new(MON+"ku_zombie")->move(TO);
		new(MON+"ku_zombie")->move(TO);
	}
	if(!present("wight")) {
		new(MON+"ku_wight2")->move(TO);
		new(MON+"ku_wight2")->move(TO);
	}
}

void create() {
	::create();
	set_property("light", 1);
	set_property("night light", -3);
	set_property("indoors", 0);
	set("short", "A runed covered tube");
	set("long",
		"Standing at the bottom of the large tube, you see that this "
		"bottom is actually a small grotto carved out into the side "
		"of the cliff.  The remains of boat moorings rust away in "
		"the shallow water.  To the north and east is one of the two "
		"large rivers which flow around Kuril."
	);
	set_items( ([
		"tube": "It is directly above you.  Way up there is the "
			"opening that leads to the streets of Kuril.",
		"cliff": "On an second examination of the rocks it does not "
			"display the layered patterning of the surrounding "
			"cliff walls.  You wonder if this is really a "
			"natural formation",
		({"remains", "moorings"}): "It appears that there may have "
			"been very heavy river trafic here at one time.",
		"river": "It's current flows swiftly by you.",
		"runes": (: call_other, this_object(), "look_rune" :),
		"walls": "They offer no purchase at all!  The runes which "
			"cover them are obviously magical in nature."
	]) );
	set_exits( ([
		"up": ROOMS+"ntube3",
		"north": ROOMS+"r22",
		"east": ROOMS+"r21"
	]) );
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
	if(!this_player()->query_flying()) {
		write("You try and flap your arms around but you just can not "
			"fly.");
		say(this_player()->query_cap_name() + " flaps " +
			this_player()->query_possessive() + " arms around "
			"but doesn't leave the ground.");
		return 1;
	}
	if(this_player()->query_flying()) {
		write("You fly up the tube.");
		tell_room("/wizards/nevin/kuril/tubes/ntube3",
			this_player()->query_cap_name() + "flies up from " +
				"the depths below.");
	}
}

int no_exit() { return 1; }
