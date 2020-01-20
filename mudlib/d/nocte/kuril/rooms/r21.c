// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	if(TP->check_kuril_river_mob()) { add_action("no_exit", "west"); }
}

void reset() {
	::reset();
	if(!present("fowl")) { 
		new(MON+"fowl")->move(TO);
		new(MON+"fowl")->move(TO);
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
		"To the west you can see a small grotto cut away from the "
		"cliff.  Inside you can see the rusted remains of metal "
		"structures."
	);
	set_items( ([
		"grotto": "The water appears to be very shallow there.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northwest": ROOMS+"r22",
		"east": ROOMS+"r20",
		"west": ROOMS+"ntube4"
	]) );
}

int no_exit() { return 1; }
