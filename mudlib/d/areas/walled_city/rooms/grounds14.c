#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "North Street.");
	set("long", "Standing inside of the west gate entrance you notice that the main passage through the Walled City turns north here. To the east a less traveled path leads into the residential section of town and to the south the military forces have their headquarters.");

	add_exit(ROOMS+"grounds13","north");
	add_exit(ROOMS+"grounds29","south");
	add_exit(ROOMS+"grounds15","east");
	add_exit(ROOMS+"grounds32","west");
	set_items(([
	({ "passage", "path" }) :
		"The roadway branches here with well travelled, dirt trails leading west and north. To the east lies a small residential area and to the south is the headquarters for the troops who protect Walled City.",
	({ "room", "walls", "floor", "trail", "trails" }) :
		"A busy intersection within the Walled City."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is quiet.");

}
