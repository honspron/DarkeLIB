// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
inherit "/wizards/nevin/std/kuril_river";

void reset() {
	::reset();
	if(!present("fowl")) { new(MON+"fowl")->move(TO); }
	if(query_night()) {
		if(!present("ghost")) { new(MON+"ghost")->move(TO); }
	}
}

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"The mist is becoming very thick near the surface of the "
		"river.  You can hardly see twenty feet in front of you.  "
		"The faint outlines of the cliff tops above you help you "
		"to stay in the middle of the river."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"mist": "It appears to be getting thicker to the northeast."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r13",
		"southwest": ROOMS+"r11"
	]) );
}
