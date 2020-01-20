#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

	set_property("light", 1);
	set_property("indoors", 0);

       set("short", "Forest path.");
       set("long", "You stand amongst the tall trees. The timber is tall here, branches reaching towards the sky. To the north the path slopes up, while to the south it drops down deeper into the forest.");

   add_exit(ROOMS+"forestpath18","north");
   add_exit(ROOMS+"forestpath16","south");

	set_items(([
	({ "leaf", "leaves", "branches" }) :
	"The branches are heavy with thick, green leaves.",
	({ "tree", "trees", "oak", "oaks", "timber" }) :
	"Mighty oaks dominate this part of the forest."
]));

	set_smell("default", "The smell of burnt leaves is strong here.");
	set_listen("default", "Small animals scurry through the bushes.");

}
