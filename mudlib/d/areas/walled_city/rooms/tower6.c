#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Northwest Tower.");
	set("long", "This tower protects the northwest corner of the walled city.");

	add_exit(ROOMS+"tower7","south");
	add_exit(ROOMS+"tower5","east");
	add_exit(ROOMS+"grounds5","down");

	set_listen("default", "The wind whistles by your ears at this height.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());

}
