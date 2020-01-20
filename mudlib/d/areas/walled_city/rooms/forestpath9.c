#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();
	set_property("light", 1);
	set_property("outdoors", 0);

	set("short", "Forest clearing.");
	set("long", "The tall oak trees give way to a grassy clearing dominated by a huge boulder set exactly at it's center. The trail ends here and the only exit is back the way you came.");

	add_exit(ROOMS+"forestpath8","southeast");

	set_items(([
	({ "leaf", "leaves" }) :
	"Large and thick green leaves.",
	({ "tree", "trees", "oak", "oaks" }) :
	"Mighty oaks stand tall above the forest floor.",
	({ "rock", "rocks", "boulder" }) :
	"This massive old chunk of rock has a crudely lettered warning carved on it. Beware the Dragon!"
	]));

	set_smell("default", "The air is moist and smells of new growth.");

	set_listen("default", "You hear croaking frogs nearby.");

	new(MON+"frog.c")->move(this_object());
	
}
