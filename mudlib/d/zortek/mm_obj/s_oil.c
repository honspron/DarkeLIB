#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "saffron oil");
   set("id", ({ "oil", "saffron oil", }));
   set("short", "saffron oil");
   set("long",
  "This is a cup of saffron oil.");
   set("weight", 15);
   set_value(4313+random(350));
}
