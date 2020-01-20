//	Wizard:	Glitch
//	Swamp	
//	sw3.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set_property("night light", 1);
	set_property("indoors", 0);
	set("short", "Swamp");
	set("long", "You're walking on a path through the swamp, and find "+
		    "yourself in a small clearing.  In the center of the "+
		    "clearing is a small hut.");
	add_exit("sw24","northwest");
	add_exit("hut","hut");
	set_items(([ "path" : "A narrow path through the swamp.",
		({ "clearing" }) : "A small clearing in the trees.  In the "+
		"center of the clearing is a hut.",
		({ "hut" }) : "The hut is made of mud, grass and wood." ]));
	set_smell("default", "You smell the strong scent of rotting "+
		"vegetation and stagnant water.");
	set_listen("default", "You hear occasional buzzing noises near your "+
		"ears.  Off in the distance, you hear a slurping sound.");
}
