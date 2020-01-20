#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("indoors", 3);

	set("short", "Lower guard tower.");
	set("long", "Here is where the guards come to rest on short breaks. A small rumpled cot set against the south wall and the two wooden stools are the only furnishings.");

	add_exit(ROOMS+"tower8","up");
	add_exit(ROOMS+"grounds6","east");
	set_items(([
	({ "cot", "bed" }) :
		"A hard looking cot covered by a rumpled blanket.",
	({ "chair", "stools", "stool" }) :
		"A wooden stool with 3 legs."
	]));
	set_smell("default", "Stale tobacco smoke hnags in the air.");
	set_listen("default", "It is quiet.");

}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
