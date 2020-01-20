#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "Above the city this covered walkway allows safe movement between the guard towers.");

	add_exit(ROOMS+"tower24","north");
	add_exit(ROOMS+"tower20","south");

	
}
