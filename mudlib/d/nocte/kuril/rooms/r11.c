// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
inherit "/wizards/nevin/std/kuril_river";

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"Small birds fly about looking for food.  A mist is begining "
		"to rise from the river obscuring your view to the northeast."
	);
	set_items( ([
		({"birds", "bird"}): "They flit about catching insects to "
			"eat.  Hmm...perhaps they are actually bats",
		"insects": "They appear to be just small spots flying about "
			"near the river.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"mist": "It appears to be getting thicker the farther up "
			"river you go."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r12",
		"west": ROOMS+"r10"
	]) );
}
