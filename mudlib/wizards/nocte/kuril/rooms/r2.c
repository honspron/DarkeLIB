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
	if(!present("fowl")) { new(MON+"fowl")->move(TO); }
	if(query_night()) { 
		if(!present("ghost")) {new(MON+"ghost")->move(TO); }
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
		"Floating along the river, you can see one of the arches of "
		"Kuril to the north.  "
		"Strange how it just sits there.  Staring out at the arch "
		"you recall childhood stories of magical elven gates that "
		"could transport you to different places...nah, couldn't be.  "
		"Far to the west is the ocean."
	);
	set_items( ([
		({"city", "kuril", "waterfront"}): "What a filthy town.",
		"ocean": "It is wide and expansive.  Although you cannot see "
			"it, you know that there is a large continent far to "
			"the west.",
		"arch": "Standing silently, you wonder what purpose they may "
			"have had here in Kuril.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The scent of the ocean fills your nose.");
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"north": ROOMS+"thieves_court4",
		"east": ROOMS+"r3",
		"west": ROOMS+"r1"
	]) );
}

int no_exit() { return 1; }
