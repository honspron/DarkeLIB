// /wizards/excelsior/cape/rooms/town1

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",0);
	set("short","Welcome to South Cape- Where the fish are bigger!");
	set("long","You stand before a large sign reading \"Welcome to South "+
		"Cape- Where the fish are bigger!\" You can't help but crack up at "+
		"this. How corny can you get! As you look around you come to the "+
		"conclusion that this place isn't all that bad. To the south is a "+
		"large cottage of some sort, while to the north is the South Cape "+
		"Bed and Breakfast.");
	set_items(([({"bed and breakfast","inn"}):"It doesn't look like that bad a "+
			"place to stay.",
		"sign":"It is clean clean white with black lettering and a nice "+
			"little picture of some flowers.",
		"cottage":"It is a quaint little cottage, but there are no signs "+
			"indicating what it could be. Your curiosity is piqued."]));
	set_exits((["west":"/wizards/excelsior/cape/rooms/rm2",
		"north":"/wizards/excelsior/cape/inn/entrance",
		"east":"/wizards/excelsior/cape/rooms/town2",
		"south":"/d/damned/guilds/tinker/entrance"]));
}
