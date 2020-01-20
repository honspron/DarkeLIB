#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("outdoors", 1);
	set_property("light", 1);
	set_short("The Entrance to the Graveyard");
	set_long("Infront of you is a large iron arch-way covered with vines and spider webs, the arch-way denotes that this is the Akkad graveyard.  The graveyard is surrounded by ten feet tall, one foot think granite walls topped with broken glass, to keep intruders out and the permanent guests inside.");
	set_items(([
	"wall" : "The walls are worn out by weather and hooligans.",
	"arch-way" : "The arch way is old and fragile.",
	]));
	set_listen("default", "It is deathly silent here.");
	set_smell("default", "The air smells stale.");
	set_exits( ({
	"/d/damned/akkad/ak_out2",
	"/d/damned/guilds/necromancer/grave1",
	}),({
	"south", "north"
	}));
}


