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
	set("long", "You're walking on a path through a swamp.  Trees lay "+
		     "tumbled in the water.  There roots, sticking up and "+
		     "looking like arms reaching for you.  Small clumps of "+
		     "grass stick up here and there.  A large tree has "+
		     "fallen and spans a large expanse of water to the "+
		     "south.");
	add_exit("sw12","north");
	add_exit("sw10","south");
	set_items(([ "path" : "A narrow path through the swamp.",
		  ({ "tree","trees" }) : "The trees are for the most part "+
		  "dead.  Some have fallen over and lay rotting in the "+
		  "water.  A few remain alive.  The large one to the north "+
		  "appears to be crossable.",
		  ({ "water" }) : "Stagnant, murky water that stinks.",
		  ({ "root","roots","arm","arms" }) : "The roots from the "+
		   "fallen trees resemble arms reaching up from the dark "+
		   "water.",
		  ({ "grass","clumps" }) : "Small patches of rough grasses "+
		     "sticking up from the swamp." ]));
	set_smell("default", "You smell the strong scent of rotting "+
		"vegetation and stagnant water.");
	set_listen("default", "You hear occasional buzzing noises near your "+
		"ears.  Off in the distance, you hear a slurping sound.");
}

