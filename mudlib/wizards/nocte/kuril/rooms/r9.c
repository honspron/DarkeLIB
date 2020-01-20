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
		"To the west is the school of necromancy.  Figures can be "
		"seen walking within the school.  It is said that the "
		"necromancers have agents scattered throughout the world, "
		"recruiting any young person who shows a talent for the "
		"magical arts.  The river flows past the school toward the "
		"ocean."
	);
	set_items( ([
		"ocean": "You are unable to see it from here.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"figures": "Hidden by shadows and poor lighting, you can "
			"make out nothing.",
		"school": "It looms over you to the west."
	]) );
	set_listen("default", "A scream pierces the air.");
	set_exits( ([
		"northeast": ROOMS+"r10",
		"southwest": ROOMS+"r8"
	]) );
}
