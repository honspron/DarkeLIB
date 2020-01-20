#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"
inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   add_exit(MONKROOMS+"room24", "west");
   add_exit(MONKROOMS+"room20", "east");
   set("short","Village path");
   set("long",
"This is a village path leading west to the monks meditation "
"area.  To the east are some structures, farther east is "
"a clearing.  Monks come and go, eager to get there work "
"done for the day.");
   add_item("clearing","A small clearing with a well in the middle");
   add_item("structures","A large building and hut lie to the east");
   add_item("path","A path leading to the western outskirts of town.");
}
void reset() {
  ::reset();
   if(!present("monk"))
   new(MONKMOBS+"monk1.c")->move(this_object());
   if(!present("gardener"))
   new(MONKMOBS+"monk_gardener.c")->move(this_object());
}
