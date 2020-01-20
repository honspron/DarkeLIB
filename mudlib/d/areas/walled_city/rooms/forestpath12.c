#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();
	set_property("light", 0);
	set_property("outdoors", 0);

    set("short", "Forest path.");
    set("long", "You stand in a heavily forested area. The tall trees tower grow high above you. Dark and thick, their leaves block out all natural light.");

   add_exit(ROOMS+"forestpath11","south");
   add_exit(ROOMS+"forestpath13","north");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, and block out all natural light from the sky.",
	({ "tree", "trees", "oak", "oaks" }) :
	"The mighty hardwoods loom high above you."
]));
	
	

}
