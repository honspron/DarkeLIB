#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Residence Row.");
	set("long", "Deep within the security of Walled City the dwarfs have made comfortable homes for their families.");

	add_exit(ROOMS+"grounds16","north");
       add_exit(ROOMS+"grounds23","south");
	add_exit(ROOMS+"grounds19","east");
	add_exit(ROOMS+"grounds27","west");
	set_items(([
	({ "homes", "cottages" }) :
		"Neatly built stone cottages.",
	({ "room", "walls", "floor" }) :
		"A quiet residential area."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
