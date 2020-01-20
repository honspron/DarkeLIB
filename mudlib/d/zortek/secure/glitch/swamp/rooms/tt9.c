//	Wizard: Glitch
//	Trolltown
//	tt9.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set("short","Path");
	set("long", "You standing in a large open area in the midst of "+
		"Troll town.  The area is covered in thick mud.");
	add_exit("tt8","east");
	add_exit("tt5","southeast");
	add_exit("hut1","hut");
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
