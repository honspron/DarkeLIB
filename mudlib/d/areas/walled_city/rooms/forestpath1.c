#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
        set_property("light", 1);
        set_property("outdoors", 0);
	set("short", "Forest path entrance.");
        set("long", "You stand in the entrance to a heavily forested area. The tall oak trees grow high above you, their gnarled branches covered in thick green leaves form a canopy blocking out all but the strongest natural light.");

        add_exit(ROOMS+"forestpath2","west");
        add_exit("/d/damned/virtual/room_6_35.world","east");
	set_items(([
        	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick.",
		({ "tree", "trees", "oaks", "oak" }) :
	"The mighty oaks stand tall above the forest floor.",
		({ "cricket" }) :
	"A cricket sits on a log."
		]));
	set_smell("default", "The smell of the forest prevades your nostrils.");
	set_listen("default", "You hear only your soft footsteps on the grassy floor.");

}
