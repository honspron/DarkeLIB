#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "Above the city you walk the protected pathway between guard towers.");

	add_exit(ROOMS+"tower1","east");
	add_exit(ROOMS+"tower3","north");
	add_exit(ROOMS+"tower26","south");

	set_listen("default", "The wind blows softly.");
}
