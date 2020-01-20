#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "You stand just south of the general store. An entrance to one of the cities many guard towers is also here.");


	add_exit(ROOMS+"grounds1","south");
	add_exit(ROOMS+"tower3","up");
	add_exit(ROOMS+"grounds3","west");
	add_exit(ROOMS+"genshop","north");

	set_items(([
	({ "tower" }) :
		"A solidly build rock tower from which the guards protect the city.",
	({ "store", "general store" }) :
		"The entrance to a general store lies to the north."
	]));
	set_smell("default", "The chill mountain breeze carries the scent of smoke and cinders.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
