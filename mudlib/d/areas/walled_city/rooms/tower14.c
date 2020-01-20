#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard tower.");
	set("long", "This tall tower protects the walled city.");

	add_exit(ROOMS+"tower13","east");
	add_exit(ROOMS+"grounds31","down");

	set_listen("default", "The wind whistles by your ears.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
