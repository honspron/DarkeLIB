#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Residence Row.");
	set("long", "A quiet little residential area within the walled city. Small dwarven cottages are home to the villagers.");

	add_exit(ROOMS+"grounds15","north");
	add_exit(ROOMS+"grounds26","south");
	add_exit(ROOMS+"grounds28","east");
	add_exit(ROOMS+"grounds29","west");
	set_items(([
	({ "dirt", "path" }) :
		"describe the dirt path.",
	({ "room", "area", "cottages" }) :
		"Tiny dwarven homesites along a well maintained road."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
