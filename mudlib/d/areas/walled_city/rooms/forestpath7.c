#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 0);
	set_property("outdoors", 0);

   	set("short", "Forest path.");
   	set("long", "You stand in a heavily forested area. Tall oak trees grow high above you, and their thick, green leaves block out all natural light. As you look around you see only more trees.");

	add_exit(ROOMS+"forestpath8","north");
  	add_exit(ROOMS+"forestpath6","south");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, and block out all natural light from the sky.",
	({ "tree", "trees", "oak", "oaks" }) :
	"The mighty oaks stand tall above the forest floor."
	]));
	
	set_smell("default", "The smells of the forest prevade your nostrils.");
	set_listen("default", "You hear only your own  soft footsteps on the forest floor.");

}
