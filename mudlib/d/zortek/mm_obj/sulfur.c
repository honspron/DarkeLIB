#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "sulfur");
   set("id", ({ "sulfur", }));
   set("short", "sulfur");
   set("long",
  "This is a handful of sulfur.");
   set("weight", 15);
   set_value(130+random(30));
}
