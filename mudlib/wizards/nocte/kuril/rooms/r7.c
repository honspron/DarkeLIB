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
		"The river continues past the city of Kuril.  Small plants "
		"can be seen growing along the ravine walls.  The rocks "
		"forming the walls have horizontal stripes running all around "
		"you."
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
		"plants": "They cling for life along the cliff walls.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The scent of the ocean fills your nose.");
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r8",
		"southwest": ROOMS+"r6"
	]) );
}
