#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Soldier's Way.");
	set("long", "This wide road leads to the Guard Captain's headquarters to the west into the residential area to the north or deeper into the military compound to the east and south.");

	add_exit(ROOMS+"grounds14","north");
	add_exit(ROOMS+"grounds25","south");
	add_exit(ROOMS+"grounds23","east");
	add_exit(ROOMS+"grounds30","west");

	set_items(([
	({ "dirt", "path" }) :
		"A busy dirt roadway travelled by many guards.",
	({ "room", "walls", "floor" }) :
		"A busy intersection within Walled City."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
