// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void reset() {
	::reset();
	if(!present("fowl")) { 
		new(MON+"fowl")->move(TO);
		new(MON+"fowl")->move(TO);
	}
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
		"Directly to the north you can see the remains of a small "
		"village that was nestled along a small beach at the base "
		"of the cliff.  Parts of it where once cut into the cliff "
		"itself.  Now it is nothing but an abandoned ruin.  The "
		"river flows swiftly onward to the west."
	);
	set_items( ([
		"village": "Perhaps a small fishing village long ago, "
			"it is now abandoned and empty.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r17",
		"west": ROOMS+"r19"
	]) );
}
