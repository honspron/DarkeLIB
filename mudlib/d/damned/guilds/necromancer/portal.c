// Darkemud

#include <std.h>
inherit ROOM;

void init() {
	::init();
//         add_action("no_south", "south");
}

void create() {
	::create();
	set_property("indoors", 1);
	set_property("light", 0);
	set_property("no castle", 1);
	set("short", "Room of Darkness");
	set("long",
		"Voices echo off of the walls around you.  Haunting voices, "
		"haunted voices, crying out to you.  Crying out at your "
		"mortality...  A large black expanse fills the south "
		"direction.  You fear what may await you in such utter "
		"emptiness."
	);
	set_items( ([
		"expanse": "Who knows what awaits you beyond that smothering "
			"hole of darkness."
	]) );
	set_listen("voices", "The cry out in pain and misery and not being "
		"able to finally rest.");
	set_exits( ([
		"east": "/d/nocte/kuril/rooms/entrance",
		"south": "/d/damned/guilds/necromancer/maus"
	]) );
}

int no_south(string str) {
	if(wizardp(TP)) { return 0;}
	if(TP->query_class() == "necromancer") { return 0; }
	if(TP->is_pet()) { return 0; }
	if(TP->query_class() == "child") { return 0; }
	message("info", "You attempt to take a step northward but "
		"your body just freezes up!  Fears from your "
		"childhood surface and force you to you knees.  You "
		"cannot go any further.", TP);
	message("info", TPQCN+" collapses into a ball of shivering "
		"terror.  Crying like a baby "+TPQCN+" eventually "
		"manages to stand up.", ENV(TP), ({TP}) );
	return 1;
}
