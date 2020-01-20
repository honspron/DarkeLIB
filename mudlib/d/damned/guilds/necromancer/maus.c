// Darkemud

#include <std.h>
inherit "/std/vault";

void init() {
	::init();
//         add_action("no_north", "north");
}

void create() {
	::create();
	set_property("indoors", 1);
	set_property("light", 0);
	set_property("no castle", 1);
	set("short", "Pitch Black Mausoleum");
	set("long",
		"Darkness swirls around you.  Gothic statues gaze down "
		"upon you with icy stares.  An unnatural coldness fills "
		"this ancient mausoleum.  You notice that you have begun "
		"to shiver from the cold.  Rubbing your hands together "
		"can do nothing to fend of the tendrils of darkness "
		"grasping at your very soul.  You have the strangest "
		"feeling that there is something to the north...waiting."
	);
	set_items( ([
		"darkness": "It is just impossible to see into it!",
		"mausoleum": "Someone very powerful must be buried in here, "
			"for the artwork and sculptures is exquisite.",
		({"artwork", "sculptures"}):  "Most has been stolen long "
			"ago, but the fine stoneworking and statues remain."
	]) );
	set_exits( ([
		"north": "/d/damned/guilds/necromancer/portal",
		"south": "/d/damned/guilds/necromancer/grave5"
	]) );
	set_door("rusty gate", "/d/damned/guilds/grave5", "south", 0);
	set_open("rusty gate", 0);
	set_locked("rusty gate", 0);
}

int no_north(string str) {
	if(wizardp(TP)) { return 0; }
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
