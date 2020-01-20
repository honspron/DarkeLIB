#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "The northern most part of this town is where the dwarves come together to buy, sell or trade their items. There is a smithy to the north of hear and you can hear the sounds of metal banging through all hours of the day or night.");

	add_exit(ROOMS+"grounds6","south");
	add_exit(ROOMS+"grounds4","east");
	add_exit(ROOMS+"tower6","up");
	add_exit(ROOMS+"armwepshop","north");
	set_items(([
	({ "room", "walls", "floor" }) :
		"This town is on the side of a mountain?"
	]));
	set_smell("default", "The disgusting stench of soot fills the air.");
	set_listen("default", "You hear banging of metal nearby.");

}
