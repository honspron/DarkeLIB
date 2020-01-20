#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Southeast guard tower.");
	set("long", "This solidly build rock tower protects the southeastern approach to the walled city.");

	add_exit(ROOMS+"tower22","south");
	add_exit(ROOMS+"tower20","west");
    add_exit(ROOMS+"grounds21","down");

	set_listen("default", "The wind whistles by your ears at this height.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
