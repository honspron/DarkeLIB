#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "High above the city this protected walkway allows easy access to all of the guard towers.");

	add_exit(ROOMS+"tower11","west");
	add_exit(ROOMS+"tower9","north");
	add_exit(ROOMS+"tower12","south");

	
}
