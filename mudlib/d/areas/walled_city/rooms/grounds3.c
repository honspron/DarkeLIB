#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "The paths that wind around this makeshift town are bustling with busy dwarves. This section is where the townsfolk gather to buy sell and trade goods or services. From here you can see a small store east and north of here around the path and several towns people running to and fro.");

	add_exit(ROOMS+"grounds2","east");
	add_exit(ROOMS+"grounds4","west");
	add_exit(ROOMS+"grounds9","south");
	set_items(([
	({ "city" }) :
		"The city bustles with dwarves milling about their business.",
	({ "room", "walls", "floor" }) :
		"The walls are thick concrete, almost fortified. There is a distinct amount of soot on them."
	]));
	set_smell("default", "The air smells of smoke.");
	set_listen("default", "You hear the sounds of dwarven men, women and children going about their daily tasks.");

}
