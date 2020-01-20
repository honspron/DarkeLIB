#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard Tower.");
	set("long", "This tall guard tower protects the walled city.");

	add_exit(ROOMS+"tower14","west");
	add_exit(ROOMS+"tower12","north");
	add_exit(ROOMS+"grounds30","down");

	set_listen("default", "The wind whistles by your ears.");
}
