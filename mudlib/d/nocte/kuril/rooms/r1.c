// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	if(TP->check_kuril_river_mob()) { add_action("no_exit", "west"); }
	if(TP->chk_my_mob()) { add_action("no_exit", "west"); }
}

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"Flowing right past the city of Kuril, you can see the ocean "
		"to the west.  To the north you can see the waterfront of "
		"Kuril.  The river flows quickly into the ocean."
	);
	set_items( ([
		({"city", "kuril", "waterfront"}): "What a filthy town.",
		"ocean": "It is wide and expansive.  Although you cannot see "
			"it, you know that there is a large continent far to "
			"the west.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The scent of the ocean fills your nose.");
	set_listen("default", "You hear waves upon the shore.");
	set_exits( ([
		"east": ROOMS+"r2",
		"west": "/d/damned/virtual/room_23_32.world"
	]) );
}

int no_exit() { return 1; }
