#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "lemon peel");
   set("id", ({ "peel", "lemon peel", }));
   set("short", "lemon peel");
   set("long",
  "This is a handful of lemon peel.");
   set("weight", 15);
   set_value(313+random(50));
}
