// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void reset() {
	::reset();
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
		"Thick billowing clouds of mist float around you.  A large "
		"waterfall to the southeast throws water all over the place.  "
		"The river flows to the west."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"rocks": "They have been worn away by the river over time.  "
			"Many layers can be seen along the sides of the "
			"ravine.",
		"layers": "Formed by the river eating away at the cliff walls "
			"it may be possible that there might be small hidden "
			"caves up along those cliff walls.",
		"waterfall": "Truly an impressive sight.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "The steady roar of a waterfall can be heard "
		"to the southeast.");
	set_exits( ([
		"southeast": ROOMS+"r15",
		"west": ROOMS+"r17"
	]) );
}
