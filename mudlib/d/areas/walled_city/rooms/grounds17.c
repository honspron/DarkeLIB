#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Warrior's walk.");
	set("long", "This intersection leads north to the shops, west to the residential areas and south and east to military posts. Dwarven guards move through the area keeping the walled city safe.");

	add_exit(ROOMS+"grounds10","north");
	add_exit(ROOMS+"grounds19","south");
	add_exit(ROOMS+"grounds18","east");
	add_exit(ROOMS+"grounds16","west");
	set_items(([
	({ "dirt", "path" }) :
		"A dirt road worn smooth by the passage of many feet.",
	({ "room", "walls", "floor" }) :
		"An intersection within the walled city."
	]));
	set_smell("default", "The cold wind chills you.");
	set_listen("default", "You hear voices from the south.");

}
