#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Residence Row.");
	set("long", "You see neatly kept dwarven cottages lining both sides of the city street.");

	add_exit(ROOMS+"grounds9","north");
	add_exit(ROOMS+"grounds16","south");
	add_exit(ROOMS+"grounds10","east");
	add_exit(ROOMS+"grounds12","west");
	set_items(([
	({ "street", "city street" }) :
		"A well maintained road through rows of small houses.",
	({ "cottages", "houses" }) :
		"Your average dwarven home."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "It is extremely quiet.");

}
