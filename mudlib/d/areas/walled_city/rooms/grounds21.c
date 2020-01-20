#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Guard barracks.");
	set("long", "You are in the guard's barracks. Hard cots line the north and east walls.");

	add_exit(ROOMS+"tower21", "up");
	add_exit(ROOMS+"grounds22", "south");
	add_exit(ROOMS+"grounds20", "west");
	
	set_items(([
	({ "barracks", "room" }) :
		"A bare walled room with cots along two walls.",
	({ "cots", "cot" }) :
		"The cots appear to be hard and uncomfortable."
	]));
	set_smell("default", "The room stinks from tobacco smoke and sweat.");
	set_listen("default", "It is quiet.");

}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
