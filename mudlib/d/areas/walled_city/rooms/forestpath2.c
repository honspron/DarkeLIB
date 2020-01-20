#include <std.h>
#include "../walled_city.h"

inherit ROOM;

void create() {
     ::create();
     set_property("light", 0);
     set_property("outdoors", 0);

          set("short", "A dark forest.");
          set("long", "You are walking through a dark and dreary forest among some very large hardwoods. The dark green leaves are so thick they block out almost all natural light. All around you you can only see more trees in an endless procession.");

          add_exit(ROOMS+"forestpath4","north");
          add_exit(ROOMS+"forestpath1","east");
          add_exit(ROOMS+"forestpath3","south");

          set_items(([
          ({ "leaf", "leaves" }) :
               "The leaves here grow large and thick, and block out almost all natural light from the sky.",
          ({ "tree", "trees", "hardwoods" }) :
                 "The mighty trunks stand tall above the forest floor and the  branches are covered in thick dark leaves."
     ]));

          set_smell("default", "The smell of the forest prevades your nostrils.");
          set_listen("default", "You hear nothing but your own soft footsteps on the forest floor.");

}
