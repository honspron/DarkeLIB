#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard tower.");
	set("long", "This solidly build rock tower guards against an attack from the east.");

	add_exit(ROOMS+"tower24","west");
	add_exit(ROOMS+"grounds18","down");

	set_listen("default", "The wind whistles by your ears at this height.");
}
