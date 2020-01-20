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
		"Dead bodies float in a small whirlpool.  Looking upward "
		"you can see the backdoor to a shop.  You seriously hope "
		"the isn't the backdoor of a tavern or pub."
	);
	set_items( ([
		"whirlpool": "Formed along the northern edge of the river, "
			"the bodies just swirl around and around.",
		"bodies": "They are just floating around.  Crabs walk upon "
			"their backs clicking their pinchers at you.  You had "
			"better not disturb their meal.",
		"ocean": "It is to the west.",
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
	set_smell("default", "The scent of the ocean fills your nose.");
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"east": ROOMS+"r26",
		"west": ROOMS+"r28"
	]) );
}
