#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 0);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "You stand on a protected walkway between guard towers.");

	add_exit(ROOMS+"tower4","east");
	add_exit(ROOMS+"tower6","west");

	
}
