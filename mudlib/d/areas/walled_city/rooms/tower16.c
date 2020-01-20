#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "This covered walkway around the city provides protected access to all of the guard towers.");

	add_exit(ROOMS+"tower15","north");
	add_exit(ROOMS+"tower17","south");

	set_listen("default", "The wind whistles softly.");
}
