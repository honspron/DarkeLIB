#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "rock salt");
   set("id", ({ "salt", "rock salt", }));
   set("short", "rock salt");
   set("long",
  "This is a handful of rock salt.");
   set("weight", 10);
   set_value(15+random(5));
}
