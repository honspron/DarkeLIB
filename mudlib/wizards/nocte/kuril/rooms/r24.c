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
		"Above you can be seen the twisted remains of a large bridge "
		"that once spanned the river.  It must have been destroyed "
		"when the City of Kuril was taken by force.  The very top "
		"of one of the arches of Kuril is barely visible above the "
		"line of the cliff top."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"bridge": "Far above you, parts of it jut out above the river "
			"on both sides of the river.",
		"arch": "Standing silently, you wonder what purpose they may "
			"have had here in Kuril.  Staring up at the arch, you "
			"are reminded of childhood stories of an elven city "
			"that had gateways to far off lands.  You struggle to "
			"remember what the name of that city was...hmmm, well, "
			"this is Kuril so it couldn't be this city.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r23",
		"southwest": ROOMS+"r25"
	]) );
}
