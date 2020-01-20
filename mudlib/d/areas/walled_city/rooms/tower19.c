#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "This covered walkway along the city wall provides access to all of the guard towers.");

	add_exit(ROOMS+"tower20","east");
	add_exit(ROOMS+"tower18","south");

	set_listen("default", "The wind whistles by your ears.");
}
