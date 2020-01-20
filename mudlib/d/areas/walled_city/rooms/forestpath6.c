#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 1);
	set_property("indoors", 0);

    	set("short", "Forest path.");
   	 set("long", "You stand in a heavily forested area. The tall old trees grow high above you, and their thick canopy of green leaves block all natural light.");
  	 add_exit(ROOMS+"forestpath5","east");
  	 add_exit(ROOMS+"forestpath7","north");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick, and block out all natural light from the sky.",
	({ "tree", "trees" }) :
	"The ancient but mighty trees stand tall above the forest floor."
]));
	set_smell("default", "The fresh clean smells of the forest fill the air.");
	set_listen("default", "A gray squirrel chitters at you from high overhead.");

}
