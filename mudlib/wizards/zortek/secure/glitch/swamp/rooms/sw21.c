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
		     "grass stick up here and there.");
	add_exit("sw20","southwest");
	add_exit("sw22","northeast");
	set_items(([ "path" : "A narrow path through the swamp.",
		  ({ "tree","trees" }) : "The trees are for the most part "+
		  "dead.  Some have fallen over and lay rotting in the "+
		  "water.  A few remain alive.",
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

void reset() {
	::reset();
	new("/wizards/glitch/swamp/mons/g_croc")->move(this_object());
}
