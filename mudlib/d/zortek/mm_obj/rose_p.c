#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "rose petals");
   set("id", ({ "petals", "rose petals", }));
   set("short", "rose petals");
   set("long",
  "This is a handful of rose petals.");
   set("weight", 8);
   set_value(25+random(15));
}
