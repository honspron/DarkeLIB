#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "incense");
   set("id", ({ "incense", }));
   set("short", "incense");
   set("long",
  "This is a handful of cheap incense.");
   set("weight", 10);
   set_value(15+random(5));
}
