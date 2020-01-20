//	Wizard:	Glitch	
//	Cavern Entrance
//	c1.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 1);
	set_property("night light", 1);
	set_property("indoors", 1);
	set("short", "Cavern");
	set("long", "The entrance to this cavern is not much more than a " +
		"narrow crack in the wall. Water drips into a glistening " +
		"pool.  A few stalactites hang from the ceiling.  The floor "+
		"appears rough at the edges, but strangely smooth down the " +
		"center.");
	add_exit("c2,"east");
	add_exit("c19","northeast");
	set_items(([
		"swamp" : "The one you are in.\n",
	({ "grass","swamp grass"}) :
	    "The grass is rather short and sickly looking.\n",
	({ "path","narrow path" }) :
	    "The path is mostly soggy earth with occassional patches of swamp grass.\n",
		"earth" : "Slightly wet earth.\n",
	({ "patch","patches" }) :
	    "Small patches of grass growing in the path.\n"]));
	set_smell("default", "The smell of rotting vegatation assails you.");
	set_listen("default", "You hear occasional slurping sounds in the distance.");
	new("/wizards/glitch/swamp/mons/ranger")->more(this_object());
}


void reset() {
	::reset();
	if(!present("ranger", this_object())) {
		new("/wizards/glitch/swamp/mons/ranger")->move(this_object());
	}
}
