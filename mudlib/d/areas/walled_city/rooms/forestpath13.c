#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

	set_property("light", 0);
	set_property("outdoors", 0);

    set("short", "Forest path.");
    set("long", "You are in a heavily forested area. The tall trees tower high above you, their thick, green leaves blocking out all natural light.");

   add_exit(ROOMS+"forestpath14","north");
   add_exit(ROOMS+"forestpath12","south");

   set_items(([
   ({ "leaf", "leaves" }) :
   "The leaves here grow large and thick, covering the sky.",

   ({ "tree", "trees" }) :
   "The mighty trees stand tall above the forest floor."
]));

  
}
