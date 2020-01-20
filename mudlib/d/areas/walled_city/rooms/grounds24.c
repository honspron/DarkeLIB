#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Beneath Twin Towers.");
	set("long", "A quiet storage area beneath the Twin Towers of the south wall. Boxes and bags are stacked neatly against the walls.");

	add_exit(ROOMS+"grounds23","north");
	add_exit(ROOMS+"tower18","up");

	add_exit(ROOMS+"grounds25","west");
	set_items(([
	({ "boxes", "bags" }) :
		"Contents unknown.",
	({ "room", "walls", "floor" }) :
		"A storage area."
	]));
	set_smell("default", "The air smells of charred flesh.");
	set_listen("default", "It is extremely quiet.");

}
