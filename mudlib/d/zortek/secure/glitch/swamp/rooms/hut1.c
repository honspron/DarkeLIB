//	Wizard:  Glitch
//	Trolltown
//	hut1.c

#include <std.h>

inherit ROOM;

void create() {
::create();
set_property("light",3);
set_property("indoors", 1);
set("short", "hut");
set("long", "You are standing in a crude hut.  Thick smoke curls from a "+
"sputtering fire.  Over the fire, a caldron hangs with some noxious brew "+
"boiling.  A crude table and chairs sit in the center of the room, and old "+
"furs lay scattered around one corner.");
add_exit("tt9","east");
set_items(([
"fire" : "The fire sputters and spews a thick smoke.",
({ "chair","chairs" }) : "The chairs are very crude but appear like they can "+
"support a heavy weight.",
({ "table" }) : "The table is made of some thick and heavy wood, numerous "+
"scars from knives can be seen in the wood.",
({ "fur","furs" }) : "Ratty looking furs which have seen much better days."
]));
set_smell("default","The smell of smoke is thick in the air.");
set_listen("default","You hear crackles and sputtering from the fire.");
}
