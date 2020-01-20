// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"If there was ever a place you did not want to be, this is "
		"it.  Like a leech upon flesh, a dark temple hovers above you "
		"to the north.  Draped upon the rock of Kuril, it hangs over "
		"the top of the cliff and descends to the banks of the river.  "
		"You cannot see anybody inside the structure, but you are "
		"absolutely sure that someone, or something, is watching you."
	);
	set_items( ([
		({"city", "kuril", "waterfront"}): "What a filthy town.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"temple": "The sight of that foul building gives you a "
			"uneasy feeling...",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r5",
		"west": ROOMS+"r3"
	]) );
}
