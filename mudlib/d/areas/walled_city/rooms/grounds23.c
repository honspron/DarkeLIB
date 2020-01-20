#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Soldier's Way.");
	set("long", "This is definetely the military side of the walled city. Armoured guards move through the area with purposeful looks on thier faces. To the north is a residential area. To the east is the drill field. To the south and west you see gaurd towers.");

	add_exit(ROOMS+"grounds28", "north");
	add_exit(ROOMS+"grounds24", "south");
	add_exit(ROOMS+"grounds20", "east");
	add_exit(ROOMS+"grounds26", "west");
	set_items(([
	({ "tower", "towers" }) :
		"Tall guard towers made from black rock set atop the city's thick rock walls.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within the walled city."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
