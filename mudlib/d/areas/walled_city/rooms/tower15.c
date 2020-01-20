#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City Wall.");
	set("long", "This walkway around the city provides protected access to all of the guard towers.");

	add_exit(ROOMS+"tower12","west");
	add_exit(ROOMS+"tower16","south");

	set_listen("default", "The wind whistles softly.");
}
