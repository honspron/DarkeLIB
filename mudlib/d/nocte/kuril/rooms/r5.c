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
		"The dark temple hangs above you to the north.  You notice "
		"that is it particularly quiet along this part of the river.  "
		"The birds and animals that are abundant elsewhere will have "
		"no part with that temple, perhaps you should do the same."
	);
	set_items( ([
		({"city", "kuril", "waterfront"}): "What a filthy town.",
		({"birds", "bird"}): "They nowhere to be found!",
		"temple": "The sight of that foul building gives you a "
			"uneasy feeling...",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r6",
		"southwest": ROOMS+"r4"
	]) );
}
