#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Residence Row.");
	set("long", "The residential area where brightly painted cottages make homes for the citizens of Walled City.");

	add_exit(ROOMS+"grounds8","north");
	add_exit(ROOMS+"grounds15","south");
	add_exit(ROOMS+"grounds11","east");
	add_exit(ROOMS+"grounds13","west");
	set_items(([
	({ "cottages", "cottage", "home", "homes" }) :
		"Your average dwarven home.",
	({ "room", "walls", "floor" }) :
		"A nice residential section of Walled City."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
