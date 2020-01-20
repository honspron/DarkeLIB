#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "High above the city this protected walkway allows easy access to all of the guard towers.");

	add_exit(ROOMS+"tower7","north");
	add_exit(ROOMS+"tower10","south");

	
}
