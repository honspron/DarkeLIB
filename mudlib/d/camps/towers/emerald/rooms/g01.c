/*
   The Towers of Tanfer'Min: The Emerald Tower
   Room coded by Duridian for DarkeMud.
*/
 
#include <std.h>
inherit "/std/vault";
 
void create() {
   ::create();
   set_property("light", 2);
   set_property("indoors", 0);
   set("short", "Outside the Emerald Tower");
   set("long",
   "The first of the towers of Tanfer'Min, the Emerald Tower stretches "
   "far into the sky, practically scraping the clouds.  Made of polished "
   "granite, the structure looms over the tallest trees in the forest, "
   "dwarfing everything around it.  A heavy oak door is set into the "
   "western side of the round tower, while a small ring of pruned grass "
   "surrounds the building."
 
   );
   set_door("door", PATH+"t11", "door", 0);
   set_smell("default", "The air is clean and fresh.");
   set_listen("default", "A bird chirps in the distance.");
   set_items( ([
   ({"tower", "emerald tower"}):
   "The first of the towers built by the arch-mage Tanfer'Min, the Emerald "
   "Tower is a marvel of modern architecture.  Made of highly-buffed "
   "granite, the structure looks quite formidable from this vantage point.  "
   "There is an oak door in the west side of the tower.",
 
   ({"clouds"}): "The clouds are white and fluffy.",
 
   ({"granite"}): "The granite that comprises the tower was very highly "
   "polished and looks quite impressive.",
 
   ({"trees", "forest"}): "The tower stands in a small clearing of the forest.",
 
   ({"grass"}): "The pruned grass runs around the circumference of the tower.",
 
   ({"door", "oak door"}): "Engraved into the door is carved the word \"Emerald\".",
                ]) );
 
   set_exits( ([
           "out": "world exit",
           "northeast": PATH+"g02",
           "southeast": PATH+"g04",
           "door": PATH+"t11",
                ]) );
}
 
void reset() {
   ::reset();
   set_open("door", 0);
   set_locked("door", 0);
}
