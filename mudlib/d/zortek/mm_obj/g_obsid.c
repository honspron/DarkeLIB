#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "ground obsidian");
   set("id", ({ "obsidian", "ground obsidian", }));
   set("short", "ground obsidian");
   set("long",
  "This is a handful of ground obsidian.");
   set("weight", 15);
   set_value(351+random(51));
}
