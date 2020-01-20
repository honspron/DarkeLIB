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
		"A cloud of mist surrounds you making vision difficult.  "
		"The river flows onward to the west."
	);
	set_items( ([
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear a dull pounding to the east.");
	set_exits( ([
		"east": ROOMS+"r16",
		"west": ROOMS+"r18"
	]) );
}
