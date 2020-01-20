#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();
	set_property("light", 0);
	set_property("outdoors", 0);

    set("short", "Forest path.");
    set("long", "This heavily forested area is dominated by ancient oaks. The tall trees tower high above you and their dark green foliage blocking out all natural light.");

    add_exit(ROOMS+"forestpath11","north");
    add_exit(ROOMS+"forestpath8","west");

    set_items(([
    ({ "leaf", "leaves", "foliage" }) :
"The leaves here grow large and thick, and block out all natural light from the sky.",
({ "tree", "trees", "oak", "oaks" }) :
"The mighty oaks stand tall above the forest floor."
]));
set_smell("default", "The fresh scents of the forest refresh you.");
set_listen("default", "You hear birds chirping and the hum of insects.");

}
