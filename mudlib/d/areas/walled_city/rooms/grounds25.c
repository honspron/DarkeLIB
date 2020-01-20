#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Beneath Twin Towers.");
	set("long", "Bags and boxes are scattered about. Blood drips down the stairs and forms a small puddle on the floor.");

	add_exit(ROOMS+"grounds26","north");
	add_exit(ROOMS+"tower17","up");
	add_exit(ROOMS+"grounds24","east");

	set_items(([
	({ "bags", "boxes" }) :
		"The boxes and bags are used to store hard bread and describe the dirt path.",
	({ "room", "walls", "floor" }) :
		"A storage area beneath Twin Towers."
	]));
	set_smell("default", "The hot scent of fresh blood fills the air.");
	set_listen("default", "It is extremely quiet.");

}
