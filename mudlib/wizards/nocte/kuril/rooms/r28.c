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
		"The river carries you onward to the ocean.  You feel a "
		"sense of relief leaving that ravine behind."
	);
	set_items( ([
		"ocean": "Its fresh air and clean waters greet you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The scent of the ocean fills your nose.");
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r27",
		"west": ROOMS+"r29"
	]) );
}
