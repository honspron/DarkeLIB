#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "North Street.");
	set("long", "You are at the southern end of North Street. It is quiet here in the western quarter, all of the soldiers must be off somewhere drinking beer and playing cards.");

	add_exit(ROOMS+"grounds14","north");
	add_exit(ROOMS+"grounds30","south");
	add_exit(ROOMS+"grounds27","east");

	set_items(([
	({ "dirt", "path" }) :
		"Dirt walked upon by enough feet to create a pathway.",
	({ "room", "walls", "floor" }) :
		"This one is like all the others here in the walled city."
	]));
	set_smell("default", "A cold breeze blows on the back of your neck.");
	set_listen("default", "It is extremely quiet.");

}
