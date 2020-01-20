#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

	set_property("light", 1);
	set_property("outdoors", 0);

  	set("short", "Forest path.");
        set("long", "You stand in a forested area. The tall trees grow high above you, their leaves growing thick and dark. To the west the trail enters a forest so dense sunlight never reaches the ground.");

   add_exit(ROOMS+"forestpath14","west");
   add_exit(ROOMS+"forestpath16","north");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick.",
	({ "tree", "trees" }) :
	"The mighty hardwoods stand tall above the forest floor."
]));

	set_smell("default", "The fresh smell of green growth prevades your nostrils.");
	set_listen("default", "Birds chirp in the trees all around you.");

}
