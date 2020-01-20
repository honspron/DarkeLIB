#include <std.h>
inherit ROOM;
#include "../walled_city.h"

	void create() {
	::create();

	set_property("light", 0);
	set_property("outdoors", 0);

	set("short", "Forest path.");
	set("long", "Aged oaks with huge twisted branches close the path from almost all natural light. The trail turns east here, and you spy a smaller path leading northwest.");

	add_exit(ROOMS+"forestpath7","south");
	add_exit(ROOMS+"forestpath9","northwest");
	add_exit(ROOMS+"forestpath10","east");

	set_items(([
	({ "leaf", "leaves", "branches" }) :
	"The branches are twisted and grarled and covered with leaves.",
	({ "tree", "trees", "oak", "oaks" }) :
	"The mighty oaks stand tall above the forest floor."
	]));
	set_smell("default", "The smells of the forest prevade your nostrils.");
	set_listen("default", "You hear the breeze blowing softly through the treetops.");

}
