/* Room coded by Duridian for DarkeMud. */
 
#include "std.h"
inherit ROOM;
 
void create() {
   ::create();
   set_property("light", 1);
   set_property("indoors", 1);
   set("short", "Dark Dungeon");
   set("long",
   "The corridor bends sharply from south to southwest, with a smaller "
   "passageway heading to the northeast.  All is quiet in this section "
   "of the catacombs, while moaning is heard to the south."
   );
   set_smell("default", "The air smells of smoke.");
   set_listen("default", "You hear moaning nearby.");
   set_items( ([
                ({"walls", "wall", "floor", "dust"}):
        "The walls and floor are covered in a thin layer of dust.",
                ({"torches", "small torches"}):
        "The small torches that are affixed to the wall provide very little light.",
                ]) );
   set_exits( ([
                "northeast": PATH+"catac128",
                "southeast": PATH+"catac143",
                "south": PATH+"catac126",
                ]) );
}
 
void reset() {
   object ob;
   ::reset();
   if(!present("skeleton")) {
      ob = new(MON_PATH+"skeleton");
      ob->move(this_object());
      ob->set("aggressive", 1);
   }
}
