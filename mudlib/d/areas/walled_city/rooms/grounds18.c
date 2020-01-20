#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Barracks");
	set("long", "This is the guard's barracks. Cots line the north and south walls. This is where weary guardsmen rest between bouts of protecting the city.");

	add_exit(ROOMS+"tower25","up");
	add_exit(ROOMS+"grounds17","west");
	set_items(([
	({ "cot", "cots" }) :
		"Hard wooden cots, each with a neatly folded blanket.",
	({ "room", "walls", "floor", "barracks" }) :
		"This rooms only furnishings are cots lined neatly along the north and south walls."
	]));
	set_smell("default", "The air is stale and smells of unwashed bodies.");
	set_listen("default", "You hear footsteps from above.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
