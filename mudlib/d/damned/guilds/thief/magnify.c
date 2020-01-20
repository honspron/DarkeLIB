/* Magnifying glass coded by Duridian.
   Needed to use the consider lock skill. */
 
#include <std.h>
inherit "/std/Object";
 
void create() {
   ::create();
   set_name("magnifying glass");
   set("id", ({"magnifying glass", "glass"}) );
   set("short", "magnifying glass");
   set("long",
   "This small magnifying glass has a polished oak handle and a thick "
   "glass lens.");
   set_weight(25);
    set_value(1000);
}
 
