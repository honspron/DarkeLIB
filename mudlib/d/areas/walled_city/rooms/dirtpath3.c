#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 0);

     set("short", "Dirt path.");
     set("long", "The path climbs steeply to the west. To the east it ends in a sharp drop where a huge slab of rock has sheered away.");

     add_exit(ROOMS+"dirtpath2","down");
     add_exit(ROOMS+"dirtpath4","west");

     set_items(([
          ({ "dirt", "path" }) :
          "A dirt path well worn from the passage of many feet leads west.",
          ({ "rock" }) :
          "A massive wedge shaped boulder which has lost its battle with gravity.",
          
     ]));
     
     set_listen("default", "It is very quiet.");

}
