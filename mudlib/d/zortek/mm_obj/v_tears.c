#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "virgin tears");
   set("id", ({ "tears", "virgin tears" }));
   set("short", "virgin tears");
   set("long",
  "This is a cup of virgin tears.");
   set("weight", 15);
   set_value(19750+random(9750));
}
