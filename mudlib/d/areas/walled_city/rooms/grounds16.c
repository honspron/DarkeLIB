#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Residence Row.");
	set("long", "A quiet neighborhood on a quiet street.");

	add_exit(ROOMS+"grounds11","north");
	add_exit(ROOMS+"grounds28","south");
	add_exit(ROOMS+"grounds17","east");
	add_exit(ROOMS+"grounds15","west");
	set_items(([
	({ "dirt", "path", "street" }) :
		"A narrow street through a dwarven neighborhood.",
	({ "room", "walls", "floor", "neighborhood" }) :
		"An average looking dwarven residential area."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
