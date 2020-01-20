#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard tower.");
	set("long", "With it's neighboring tower to the north this stone fortification provides protection to the southeast section of the city.");

	add_exit(ROOMS+"tower21","north");
	add_exit(ROOMS+"grounds22","down");

	set_listen("default", "The wind whistles by your ears.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
