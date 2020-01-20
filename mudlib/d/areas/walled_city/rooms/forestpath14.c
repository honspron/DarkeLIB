#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

    set_property("light", 0);
    set_property("outdoors", 0);

    set("short", "Forest path.");
    set("long", "You stand in the darkened forest. The trees tower over you, their thick, green leaves blocking out all natural light.");

   add_exit(ROOMS+"forestpath15","east");
   add_exit(ROOMS+"forestpath13","south");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, blocking out all natural light from the sky.",
({ "tree", "trees" }) :
"The trees stand tall above the forest floor."
]));


	set_listen("default", "You hear birds chirping off to the east.");

}
