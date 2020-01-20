#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "Above the city this covered walkway allows safe access to all guard towers.");

	add_exit(ROOMS+"tower15","east");
	add_exit(ROOMS+"tower13","south");
	add_exit(ROOMS+"tower10","north");

	set_listen("default", "The wind whistles softly.");
}
