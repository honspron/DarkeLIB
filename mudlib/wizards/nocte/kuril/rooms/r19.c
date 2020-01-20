// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

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
		"The remains of a small village line the cliffs to the north.  "
		"Above you is the City of Kuril.  Buildings line the top of "
		"cliff.  Some are probably shops.  The river carries you "
		"downstream to the west."
	);
	set_items( ([
		({"city", "kuril"}): "Perhaps there is a way to get into the "
			"city around here.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		({"shops", "stores"}): "Some stick out beyond the edge of "
			"the cliffs supported by planks of wood wedged into "
			"the side of the ravine.  Space sure must be limited "
			"in Kuril.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place.",
		"village": "Tucked away info the side of the cliff, the "
			"village is not noticable from above."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r18",
		"west": ROOMS+"r20"
	]) );
}
