#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "black sand");
   set("id", ({ "sand", "black sand", }));
   set("short", "black sand");
   set("long",
  "This is a handful of black sand.");
   set("weight", 15);
   set_value(155+random(55));
}
