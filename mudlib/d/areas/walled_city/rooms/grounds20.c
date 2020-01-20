#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Drill area.");
	set("long", "The open square before you is where new recruits are drilled in the fundamental skills needed in warfare. To the east you see a two guard towers.");

	add_exit(ROOMS+"grounds19","north");
	add_exit(ROOMS+"grounds21","east");
	add_exit(ROOMS+"grounds23","west");
	set_items(([
	({ "square", "path", "floor" }) :
		"This once grassy square has been worn to bare earth by the many callused feet that have trod here.",
	({ "tower", "towers", "guard tower" }) :
		"Twin towers dominate the southeast corner of the walled city."
	]));
	set_smell("default", "A chill wind blows across the open square.");
	set_listen("default", "It is quiet.");
}
