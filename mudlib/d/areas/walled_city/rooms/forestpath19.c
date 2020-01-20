#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 2);
	set_property("outdoors", 0);

        set("short", "Forest path.");
        set("long", "You stand in the forest. The tall trees grow high above thier branches thick with green leaves. To the west the path climbs upward while to the south it decends deeper into the woods. ");

        add_exit(ROOMS+"forestpath20","west");
        add_exit(ROOMS+"forestpath18","south");

	set_items(([
	({ "leaf", "leaves", "branches" }) :
	"The leaves here grow large and thick, covering the branches in a coat of deep dark green.",
	({ "tree", "trees", "hardwoods", "woods" }) :
	"Tall hardwoods grow above the forest floor."
	]));

	set_smell("default", "The smell of burnt leaves is strong here.");

	}
