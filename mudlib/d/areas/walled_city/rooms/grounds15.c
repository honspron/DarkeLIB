#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("indoors", 2);

	set("short", "Residence Row.");
	set("long", "A quiet residential area, small neat cottages line the roadway.");

	add_exit(ROOMS+"grounds12","north");
	add_exit(ROOMS+"grounds27","south");
	add_exit(ROOMS+"grounds16","east");
	add_exit(ROOMS+"grounds14","west");
	set_items(([
	({ "dirt", "path", "roadway" }) :
		"A quiet street in a quiet part of town.",
	({ "room", "walls", "cottages" }) :
		"Your average dwarven homes."
	]));
	set_smell("default", "The cold wind brings the smell of charred meat to your flaring nostrils.");
	set_listen("default", "It is extremely quiet.");

}
void reset() {
	::reset();
if(!present("woman"))
{
new(MON+"dwarf_woman.c")->move(this_object());
new(MON+"dwarf_woman.c")->move(this_object());
}
}
