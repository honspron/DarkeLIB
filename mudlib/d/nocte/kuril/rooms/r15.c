// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include "nevin.h"
#define OBJ	this_player()->query_objective()

inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	add_action("block_say", "say");
}

void reset() {
	::reset();
	if(!present("fowl")) {
		new(MON+"fowl")->move(TO);
		new(MON+"fowl")->move(TO);
	}
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
	set("short", "Waterfall of Kuril");
	set("long",
		"Water slams into the rocks to the east.  A huge waterfall "
		"sends water all over the place.  If you don't move along "
		"quickly you will soon be drenched all over."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"ledge": "It appears to be a ledge carved into the side of "
			"the cliff.  Whatever it is, you have a feeling deep "
			"down that it has not been coded yet...",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"waterfall": "Around half the height of the City of Kuril at "
			"this location in the river, the waterfall is still "
			"a mighty sight."
	]) );
	set_listen("default", "Pounding water creates a deafening roar "
		"around you.");
	set_exits( ([
		"northwest": ROOMS+"r16",
		"southwest": ROOMS+"r14"
	]) );
}

int block_say(string str) {
	if(!str) { return 0;}
	if(str) {
		message("info", TPQCN+" says something but the sound of the "
			"waterfall drowns "+OBJ+" out.", ENV(TP), ({TP}) );
		message("info", "You say something but the sound of the "
			"waterfall drowns you out.", TP);
		return 1;
	}
}
