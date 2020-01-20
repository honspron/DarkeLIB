#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "Above the city this covered walkway provides easy passage between guard towers.");

	add_exit(ROOMS+"tower26","north");
	add_exit(ROOMS+"tower25","east");
	add_exit(ROOMS+"tower23","south");

	set_listen("default", "The wind whistles softly.");
}
