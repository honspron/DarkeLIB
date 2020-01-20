#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "This covered walkway provides safe access to all of the many guard towers.");

	add_exit(ROOMS+"tower23","north");
	add_exit(ROOMS+"tower19","west");
	add_exit(ROOMS+"tower21","east");

	set_listen("default", "The wind whispers softly.");
}
