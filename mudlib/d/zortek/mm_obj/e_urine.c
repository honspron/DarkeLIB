#include <std.h>
#include <daemons.h>
inherit OBJECT;
void create() {
   ::create();
   set("name", "elven urine");
   set("id", ({ "urine", "elven urine" }));
   set("short", "elven urine");
   set("long",
  "This is a cup of elven urine.");
   set("weight", 15);
   set_value(8759+random(759));
}
