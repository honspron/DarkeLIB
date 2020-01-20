#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "North Street.");
	set("long", "The main passage through Walled City goes north from here. To the east a smaller road leads to the residential area and to the south the military has it's headquarters.");

	add_exit(ROOMS+"grounds6","north");
	add_exit(ROOMS+"grounds14","south");
	add_exit(ROOMS+"grounds12","east");
	set_items(([
	({ "dirt", "path", "road", "passage" }) :
		"The main road leads north.",
	({ "room", "walls", "floor" }) :
		"A busy intersection with many travellers moving in all directions."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is quiet.");

}
