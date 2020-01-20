#include <std.h>
#include "../goblin.h"

inherit ROOM;

void create() {
	::create();
	set_property("indoors", 2);
	set_property("light", 3);
	set("short", "Further down the pebble road.");
	set("long", "Infront of you is the goblin settlement, it seems to be built into a small hill, maybe from mining purposes.  The gates of the settlement are open and only guarded by a snotling.  You wonder why they only have one snotling to guard the gates.");
	add_exit(ROOMS+"newgob1", "south"); 
	add_exit(ROOMS+"newgob3", "northwest");
	add_exit(ROOMS+"newgob4", "northeast");	
}

