// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	if(TP->check_kuril_river_mob()) { add_action("no_exit", "north"); }
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
		"Above you can be seen the chared remains of a bridge that "
		"once spanned the ravine to both sides of the cliff walls.  "
		"To the north is a small grotto and rusted fence structures."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"bridge": "Far above you, parts of it jut out above the river "
			"on both sides of the river.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"grotto": "The water looks very shallow there."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"north": ROOMS+"stube3",
		"northeast": ROOMS+"r7",
		"southwest": ROOMS+"r5"
	]) );
}

int no_exit() { return 1; }
