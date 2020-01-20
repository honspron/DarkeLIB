#include <std.h>
#include "../walled_city.h"

inherit ROOM;

	void create() {
	 ::create();

	set_property("light", 0);
	set_property("outdoors", 0);

	set("short", "A clearing in the Forest.");
	set("long", "You are in a small clearing surrounded by the the twisted trunks and broken branches of mighty oaks brought down by the sweep of God's hand. The gnarled, broken timbers block all further passage and you must return the way you came.");

	add_exit(ROOMS+"forestpath2","south");

	set_items(([
	({ "leaf", "leaves" }) :
	"The leaves here grow large and thick and are the darkest green you have ever seen.",
	({ "tree", "trees" , "oak", "oaks", "trunks", "timbers", "branches" } ) :
	"The battered hardwoods have been ravaged by a terrible storm. Their trunks are twisted and even their largest branches have been ripped asunder."
]));
	set_smell("default", "The faint smell of woodsmoke makes your nostrils flare.");
	set_listen("default", "You hear the scurrying of some small creature through the thick underbrush.");

}
