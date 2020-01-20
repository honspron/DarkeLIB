#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "A busy intersection within the walled city. North and west are the shops while to the south you can see guards training.");

	add_exit(ROOMS+"grounds1","north");
	add_exit(ROOMS+"grounds17","south");
	add_exit(ROOMS+"grounds11","west");
	set_items(([
	({ "dirt", "path" }) :
		"A busy intersection.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within the walled city."
	]));
		set_listen("default", "You hear the sound of many feet, marching slightly out of step, coming from the south.");

}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
