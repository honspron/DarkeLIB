#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "filtered water");
   set("id", ({ "water", "cup of water", "filtered water" }));
   set("short", "filtered water");
   set("long",
  "This is a cup of filtered water.");
   set("weight", 10);
   set_value(5+random(5));
}
