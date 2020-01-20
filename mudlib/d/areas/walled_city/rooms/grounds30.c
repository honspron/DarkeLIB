#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Guard Headquarters.");
	set("long", "This is where the leaders of the Walled City Guards meet to plan for the defense of the citizens.");

	add_exit(ROOMS+"grounds29","north");
	add_exit(ROOMS+"tower13","up");
	add_exit(ROOMS+"grounds31","west");
	add_exit(ROOMS+"grounds26","east");

	set_items(([
	({ "table", "chairs" }) :
		"Table and chairs are in need of repairs.",
	({ "room", "walls", "floor" }) :
		"A dirt floored room with an ancient table and five hard wooden stools."
	]));
	set_smell("default", "The air stinks of fear.");
	set_listen("default", "It is deathly quiet.");

}
void reset() {
	::reset();
if(!present("guard"))
{
new(MON+"moving_guard.c")->move(this_object());
}
}
