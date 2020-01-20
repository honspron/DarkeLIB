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
		"Continuing past the Kuril, the river takes a turn further "
		"downstream.  The occasional plant grows upon a small ledge "
		"while birds fly all about you.  An unnatural quiet surrounds "
		"you..."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		({"birds", "bird"}): "They flit about catching insects to "
			"eat.  Hmm...perhaps they are actually bats",
		"insects": "They appear to be just small spots flying about "
			"near the river.",
		"plants": "They cling for life along the cliff walls.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r19",
		"west": ROOMS+"r21"
	]) );
}
