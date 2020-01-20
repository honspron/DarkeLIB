#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 0);

     set("short", "Dirt path.");
     set("long", "Scorched black earth, partially melted rocks and the burned and blackened charred remains of a rather large animal cause you to look for the nearest safe exit. To the north a rocky trail climbs up the mountianside and out of the forest. To the south the path continues, winding down amongst the burnt and blackened trees.");

     add_exit(ROOMS+"dirtpath2","north");
     add_exit(ROOMS+"forestpath20","south");

     set_items(([
	  ({ "animal", "charred remains", "remains" }) :
	  "It is burned beyond all possible recognition.",
          ({ "rock", "rocks" }) :
	  "The rocks upon the pathway have been scorched by brief but intense heat, partially melting them.",

          ({ "dirt", "path", "trail" }) :
          "The rocky pathway is scorched black from a recent fire.",
          ({ "forest", "tree", "trees" }) :
          "Trees are burnt and blackened as if a fierce fire had blazed briefly here."
     ]));
     set_smell("default", "The stench of charred meat makes you gag.");
     set_listen("default", "It is deathily still.");

}
