#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "grain alcohol");
   set("id", ({ "alcohol", "grain alcohol" }));
   set("short", "grain alcohol");
   set("long",
  "This is a cup of grain alcohol.");
   set("weight", 15);
   set_value(250+random(50));
}
