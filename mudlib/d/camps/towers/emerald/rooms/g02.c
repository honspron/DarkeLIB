/*
   The Towers of Tanfer'Min: The Emerald Tower
   Room coded by Duridian for DarkeMud.
*/
 
#include <std.h>
inherit ROOM;
 
void create() {
   ::create();
   set_property("light", 1);
   set_property("indoors", 0);
   set("short", "Outside the Emerald Tower");
   set("long",
   "The northern side of the Emerald Tower is featureless, except for the "
   "glare produced by the glossy granite that makes up the tower.  The "
   "soft grass is neatly pruned and runs around the circumference of the "
   "the tower's base."
   );
   set_smell("default", "The air is cool and crisp.");
   set_listen("default", "It is quiet on this side of the tower.");
   set_items( ([
   ({"tower", "emerald tower"}): "The Emerald Tower climbs into the clear sky.",
   ({"granite"}): "The tower was constructed of polished granite stone.",
   ({"grass"}): "The thick grass surrounds the base of the tower.",
                ]) );
   set_exits( ([
      "southwest": PATH+"g01",
      "southeast": PATH+"g03",
                ]) );
}
