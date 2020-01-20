//	Wizard: Glitch
//	Trolltown path
//	tt2.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set("short","Path");
	set("long", "You're walking along a path in Trolltown. "+
		"Large mud and grass huts are to the east and west of the "+
		"path.");
	add_exit("tt1","south");
	add_exit("tt3","north");
	add_exit("tt4","northeast");
	add_exit("tt5","northwest");
	set_items(([
		"path" : "The path is very muddy, lots of large footprints "+
		"are all over the place.",
		({ "footprint","footprints" }) : "The footprints appear to "+
		"from numerous troll walking through the mud",
		({ "mud" }) : "A very thick mud.",
		({ "hut","huts" }) : "Primitive huts built of mud and grass. "+
		"They are very tall, but don't seem all that wide.",
		({ "grass" }) : "Swamp grasses.",
		]));
	set_smell("default", "The odor of swamp gas is very strong in here.");
	set_listen("default", "You hear an occasional gutteral word.");
}

void reset() {
	::reset();
	if(!present("female troll", this_object()) ) {
		new("/wizards/glitch/swamp/mons/f_troll")->move(this_object());
	}
	if(!present("young troll", this_object()) ) {
		new("/wizards/glitch/swamp/mons/y_troll")->move(this_object());
	}
}
