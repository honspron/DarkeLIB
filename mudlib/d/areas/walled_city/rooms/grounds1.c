#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "The fortress city surrounds you with solid rock walls.");

	add_exit(ROOMS+"grounds2","north");
	add_exit(ROOMS+"grounds10","south");
	add_exit(ROOMS+"dirtpath5","east");
	add_exit(ROOMS+"grounds9","west");

	set_items(([
	({ "walls", "wall" }) :
	"Solidy built of huge stone blocks the city walls surround you.",
	({"city"})	:
	"Be it ever so humble, there's no place like home."	
	]));
	set_smell("default", "The smell of unwashed bodies and woodsmoke makes your nose wrinkle.");
	set_listen("default", "You hear footsteps walking in unison as if a troop of soldiers were drilling nearby.");

}
