// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	if(TP->check_kuril_river_mob()) { add_action("no_exit", "south"); }
}

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
		"To the south is a small grotto beneath a large outcropping "
		"of stone.  It looks like the river cut away the base of the "
		"cliff...or that's what it is made to appear like.  The "
		"river's current quickly carries you onward to the southwest."
	);
	set_items( ([
		"grotto": "It looks safe enough to rest inside for awhile.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"southeast": ROOMS+"r21",
		"southwest": ROOMS+"r23",
		"south": ROOMS+"ntube4"
	]) );
}

int no_exit() { return 1; }
