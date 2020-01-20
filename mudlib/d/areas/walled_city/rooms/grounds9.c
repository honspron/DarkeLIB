#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled City.");
	set("long", "Deep within the solid walls is the business district. You hear the sounds of commerce to your north and package laden citizens pass by you, going quickly about their business.");

	add_exit(ROOMS+"grounds3","north");
	add_exit(ROOMS+"grounds11","south");
	add_exit(ROOMS+"grounds1","east");
	add_exit(ROOMS+"grounds8","west");
	set_items(([
	({ "dirt", "path" }) :
		"describe the dirt path.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within the walled city." 			]));
	set_smell("default", "The stench of woodsmoke drifts by on the breeze.");
	set_listen("default", "You hear load voices from the north.");

}
