#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();
set_property("light", 1);
set_property("indoors", 0);

    set("short", "Forest path.");
    set("long", "You stand on a grassy path through the forest. Tall trees grow all around, their branches heavy with leaves. To the north the path climbs upward while to the south it decends deeper into the forest.");

   add_exit(ROOMS+"forestpath19","north");
   add_exit(ROOMS+"forestpath17","south");

	set_items(([
	({ "leaf", "leaves", "branches" }) :
	"The branches are heavily covered with thick dark leaves.",

	({ "tree", "trees", "oak", "oaks" }) :
	"Mighty oaks grow tall above the forest floor."
]));
set_smell("default", "The smell of burnt leaves is strong here.");

}
