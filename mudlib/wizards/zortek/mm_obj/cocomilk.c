#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "coconut milk");
   set("id", ({ "milk", "coconut milk" }));
   set("short", "coconut milk");
   set("long",
  "This is a cup of coconut milk.");
   set("weight", 15);
   set_value(39+random(10));
}
