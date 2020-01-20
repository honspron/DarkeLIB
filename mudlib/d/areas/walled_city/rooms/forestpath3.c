#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 0);
	set_property("outdoors", -1);

	set("short", "Forest path.");
	set("long", "You stand in a heavily forested area. The ancient trees tower high above you, and their thick, green leaves block out any natural light. As you look around you see nothing but more trees in every direction.");

 	add_exit(ROOMS+"forestpath2","north");
	add_exit(ROOMS+"forestpath5","west");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, and block out all natural light from the sky.",
	({ "tree", "trees", "oak","oaks" }) :
"The mighty hardwoods stand tall above the forest floor."
]));

	set_smell("default", "The smells of the forest prevade your nostrils.");
	set_listen("default", "You hear only your soft footsteps on the forest floor.");

}
