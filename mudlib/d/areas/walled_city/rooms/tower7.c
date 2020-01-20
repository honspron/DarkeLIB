#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "Above the city this walkway connects the guard towers, allowing reinforcements to quickly move between them.");

	add_exit(ROOMS+"tower8","west");
	add_exit(ROOMS+"tower6","north");
	add_exit(ROOMS+"tower9","south");

	
}
