#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "slug slime");
   set("id", ({ "slime", "slug slime", }));
   set("short", "slug slime");
   set("long",
  "This is a cup of slug slime.");
   set("weight", 15);
   set_value(75+random(25));
}
