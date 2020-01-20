#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Northeast Tower.");
	set("long", "Above the city this tower protects the northeastern perimeter.");

	add_exit(ROOMS+"tower2","south");
	add_exit(ROOMS+"tower4","west");
	add_exit(ROOMS+"grounds2","down");

	set_listen("default", "The wind whistles by your ears at this height.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
