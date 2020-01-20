//	Wizard: Glitch
//	Trolltown
//	tt3.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set("short","Path");
	set("long", "You standing in a large open area in the midst of "+
		"Troll town.  The area is covered in thick mud.");
	add_exit("tt2","south");
	add_exit("tt4","east");
	add_exit("tt5","west");
	add_exit("tt6","north");
	add_exit("tt7","northeast");
	add_exit("tt8","northwest");
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
