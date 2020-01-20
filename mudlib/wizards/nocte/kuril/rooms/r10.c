// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
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
		"The river flows around the city of Kuril.  Above you shops "
		"edge right up to the end of the cliff.  The river's swift "
		"current carries you toward the sea."
	);
	set_items( ([
		({"shops", "stores"}): "Some stick out beyond the edge of "
			"the cliffs supported by planks of wood wedged into "
			"the side of the ravine.  Space sure must be limited "
			"in Kuril.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r11",
		"southwest": ROOMS+"r9"
	]) );
}
