// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"A thick mist fills the air.  To the northeast you can see "
		"the bottom of a large waterfall.  The rocks under the city "
		"of Kuril to the north are being slowly eaten away such that "
		"the city above now overhangs the rocks at its base."
	);
	set_items( ([
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		"waterfall": "It is to the northeast.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You can hear water pounding into rocks to the "
		"the northeast.");
	set_exits( ([
		"northeast": ROOMS+"r15",
		"southwest": ROOMS+"r13"
	]) );
}
