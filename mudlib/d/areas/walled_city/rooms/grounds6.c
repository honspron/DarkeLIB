#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "North Street.");
	set("long", "The northern section of the dwarven city is devoted to buying and selling wares. You notice several dwarven citizens hurrying past. To the west stands a guard tower built from heavy pieces of dark rock. To the north and east you see shops.");

	add_exit(ROOMS+"grounds5","north");
	add_exit(ROOMS+"grounds13","south");
	add_exit(ROOMS+"grounds7","west");
	add_exit(ROOMS+"grounds8","east");
	set_items(([
	({ "tower", "towers" }) :
		"The guard towers are constucted of large black rocks which have been chisled into massive blocks and mortered togather.",
	({ "room", "walls", "floor" }) :
		"A protected alcove just off the main business section with walls of black rock."
	]));
	set_smell("default", "The smell of smoke hangs in the air.");
	set_listen("default", "You hear the faint bang of a hammer on metal.");

}
