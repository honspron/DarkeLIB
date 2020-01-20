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
		"Shops lines the cliff top above you while to the west is "
		"the ocean.  The river's current pushes you downstream to "
		"the west."
	);
	set_items( ([
		"ocean": "It looks like a field of blue rising to meet the "
			"sky.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		({"shops", "stores"}): "Some stick out beyond the edge of "
			"the cliffs supported by planks of wood wedged into "
			"the side of the ravine.  Space sure must be limited "
			"in Kuril.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The scent of ocean air greets you.");
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r24",
		"west": ROOMS+"r26"
	]) );
}
