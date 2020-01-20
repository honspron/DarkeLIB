#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

	set_property("light", 1);
	set_property("indoors", 0);

    set("short", "Forest path.");
    set("long", "The forest is dense with tall hardwoods. You stand on a grassy path surrounded by tall tree with branches reaching upward to block out the sky. The path to the north rises steeply while the one to the south slopes down into the deep forest.");

   add_exit(ROOMS+"forestpath17","north");
   add_exit(ROOMS+"forestpath15","south");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick.",
	({ "tree", "trees", "hardwoods" }) :
	"The mighty oaks stand tall above the forest floor."
	]));

	set_smell("default", "The faint smell of burnt leaves wafts on the breeze.");
	set_listen("default", "You hear only your own soft footsteps on the grassy floor.");

}
