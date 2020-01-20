#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 0);
	set_property("outdoors", 0);

	set("short", "Forest path.");
	set("long", "You are in a heavily forested area. Tall hardwoods grow high above you and their thick, green leaves block out all natural light.");

	add_exit(ROOMS+"forestpath3","east");
	add_exit(ROOMS+"forestpath71","north");
	add_exit(ROOMS+"forestpath6","west");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, and block out all natural light from the sky.",
	({ "tree", "trees", "oak", "oaks", "hardwoods" }) :
	"The mighty oaks stand tall above the forest floor."
]));

	set_smell("default", "The smells of the forest fill your nostrils.");

	set_listen("default", "You hear only your soft footsteps on the forest floor.");

}
