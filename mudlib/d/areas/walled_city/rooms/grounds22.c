#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("indoors", 2);

	set("short", "Guard training room.");
	set("long", "Here the new recruits are trained in the use of all types of weapons. There are clubs, maces, swords and different types of armour lying around here, most of which are badly beaten and used. The room is otherwise bare save a small eastern window which allows what little light there is here, come cascading into the room from the glorious sky.");

	add_exit(ROOMS+"tower22","up");
	add_exit(ROOMS+"grounds21","north");

	set_items(([
	({ "room", "walls", "floor" }) :
	"A barren room with exits north and up.",
	({"weapons"})	:
	"The weapons are all but useless. They are merely training aids.",
	({"armour"})	:
	"Varying types of armours are strewn about the place all in desparate need of repair.",
	({"window"})	:
	"The light falls gently on the floor during the day here and at night allows only the starlit skies to peek through."
	]));
	set_smell("default", "The smell of sweat hangs in the air.");
	set_listen("default", "You hear foot steps from above.");

}
