#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "pearl powder");
   set("id", ({ "powder", "pearl powder", }));
   set("short", "pearl powder");
   set("long",
  "This is a handful of pearl powder.");
   set("weight", 15);
   set_value(1917+random(917));
}
