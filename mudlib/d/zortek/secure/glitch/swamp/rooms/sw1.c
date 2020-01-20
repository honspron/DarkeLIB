//	Wizard:	Glitch	
//	Swamp Entrance
//	sw1.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set_property("night light", 1);
	set_property("indoors", 0);
	set("short", "Swamp");
	set("long", "You find yourself at the beginning of a deep and forbidding swamp.  " +
		"A narrow path through the swamp grass leads out in to the swamp.");
	add_exit("sw2","northeast");
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
