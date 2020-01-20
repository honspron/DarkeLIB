#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "West Tower.");
	set("long", "The West Tower has been hastily rebuild. Some of the stones used in the reconstruction seem to have been scorched by flame. To the west the mountain looms, its bare rocky slopes seem uninviting.");

	add_exit(ROOMS+"tower7","east");
	add_exit(ROOMS+"grounds7","down");

	set_listen("default", "The wind whistles by your ears at this height.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
