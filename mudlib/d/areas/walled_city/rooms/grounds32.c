#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "West Gate.");
	set("long", "A massive gate made from heavy timbers and clad in iron plate stands open before you. The guards are vigilent and carefully scrutinize every passerby. Above you stands the West Tower.");

	add_exit(ROOMS+"tower11","up");

	add_exit(ROOMS+"grounds14","east");
	set_items(([
	({ "gate", "timbers", "plate" }) :
		"Massive timbers covered by iron plate form a strong gate which will hold out any attack against the Walled City.",
	({ "tower", "west tower" }) :
		"Above the gate sets a tower built of volcanic black rock. Small windows allow the guards to keep a watch on all who approach the city from the west."
	]));
	set_smell("default", "The cold wind feels like death on your skin");
	set_listen("default", "You hear the jangle of armour.");

}
void reset() {
	::reset();
if(!present("guard"))
{
new(MON+"guard.c")->move(this_object());
new(MON+"guard.c")->move(this_object());
new(MON+"moving_guard.c")->move(this_object());
}
}
