#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "diamond dust");
   set("id", ({ "dust", "diamond dust", }));
   set("short", "diamond dust");
   set("long",
  "This is a handful of diamond dust.");
   set("weight", 15);
   set_value(21815+random(1815));
}
