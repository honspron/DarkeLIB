#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "sea salt");
   set("id", ({ "sea salt", "salt" }));
   set("short", "sea salt");
   set("long",
  "This is a handful of sea salt.");
   set("weight", 10);
   set_value(10+random(10));
}
