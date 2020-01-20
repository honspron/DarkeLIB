#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 0);

     set("short", "Dirt path.");
     set("long", "The dirt path decends the steep slope to the south and you can see forest growth down below you. To the west a recent rockslide has wiped the trail away. You can see the pathway begin again 30 feet up a rocky cliff.");

     add_exit(ROOMS+"dirtpath1","south");
     add_exit(ROOMS+"dirtpath3","up");

     set_items(([
          ({ "dirt", "path", "trail", "pathway" }) :
          "A rock strewn dirt path leads south.",
          ({ "forest", "tree", "trees" }) :
          "You can see a vast forest spreading out before you to the south.",
	  ({ "cliff" }) :
	  "To the west the trail comes to an abrupt end against a jagged rock face. A slide of rocks has carried the trail away."
     ]));
         
     
}
