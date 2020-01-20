#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled City.");
	set("long", "Deep within the solid walls of the city is a busy business district. You hear the sounds of commerce to your north and package laden dwarven citizens pass by you as they go south.");

	add_exit(ROOMS+"grounds4","north");
	add_exit(ROOMS+"grounds12","south");
	add_exit(ROOMS+"grounds9","east");
	add_exit(ROOMS+"grounds6","west");
	set_items(([
	({ "dwarf", "citizen", "citizens", "dwarves" }) :
		"A common dwarf.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within the walled city."
	]));
	
	

}
