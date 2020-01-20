#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Warrior's walk.");
	set("long", "This busy intersection leads south toward the militay training ground and west toward the residential area. Far to the north you see shops.");

	add_exit(ROOMS+"grounds17","north");
	add_exit(ROOMS+"grounds20","south");

	add_exit(ROOMS+"grounds28","west");
	set_items(([
	({ "dirt", "path" }) :
		"describe the dirt path.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within the walled city."
	]));
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
