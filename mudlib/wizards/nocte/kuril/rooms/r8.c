// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void reset() {
	::reset();
	if(!present("fowl")) { new(MON+"fowl")->move(TO); }
}

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"Above you is the School of Necromancy.  Parts of the school "
		"have been built into the face of the ravine walls.  Windows "
		"near the top of the ravine walls appear to be small holes.  "
		"Occasionally you can hear scream..."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"school": "What a dark and evil place.  You shiver as another "
			"scream echoes against the ravine walls."
	]) );
	set_listen("default", "A scream bounces off the walls of the ravine "
		"around you.  It is seconds before the scream fades away.");
	set_exits( ([
		"northeast": ROOMS+"r9",	
		"southwest": ROOMS+"r7"
	]) );
}
