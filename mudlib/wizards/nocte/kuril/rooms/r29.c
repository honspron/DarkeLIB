// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void init() {
	::init();
	if(TP->check_kuril_river_mob()) { add_action("no_exit", "west"); }
	if(TP->chk_my_mob()) { add_action("no_exit", "west"); }
}

void reset() {
	::reset();
	if(!present("fowl")) { new(MON+"fowl")->move(TO); }
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
		"The ocean is before you.  To the east is a river that "
		"snakes its way around the City of Kuril.  To the south "
		"is the waterfront of Kuril.  Small shops can be seen along "
		"the roadways."
	);
	set_items( ([
		({"city", "kuril", "waterfront"}): "The piers look like a "
			"good place to enter.",
		"ocean": "You are relieved to see the open expanses of the "
			"ocean.",
		({"shops", "stores"}): "Selling all manners of goods, you "
			"will probably find something you need.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_smell("default", "The of the ocean fills your nose.");
	set_listen("default", "You hear waves upon the shore.");
	set_exits( ([
		"east": ROOMS+"r28",
		"west": "/d/damned/virtual/room_23_32.world"
	]) );
}

int no_exit() { return 1; }
