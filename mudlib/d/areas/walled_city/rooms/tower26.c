#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "City wall.");
	set("long", "This covered walkway around the city provides quick easy movement by the guards as they travel between the towers.");

	add_exit(ROOMS+"tower2","north");
	add_exit(ROOMS+"tower24","south");

	set_listen("default", "Someone farts wetly.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
