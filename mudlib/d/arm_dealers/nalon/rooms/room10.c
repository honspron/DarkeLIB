#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"
inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   add_exit(MONKROOMS+"room27", "south");
   add_exit(MONKROOMS+"room14", "west");
   add_exit(MONKROOMS+"room8", "north");
   add_exit(MONKROOMS+"room7", "east");
   set("short","Small clearing");
   set("long",
"This is a small clearing in the middle of the monk's habitat.  A "
"well lies to the north, which is the source of water for "
"the monks.  The surrounding forest is extremeley peaceful "
"and green, the animals leaving in peace.  To the south "
"some huts can be seen.");
   add_item("forest","The forest is pleasantly green.");
   add_item("well","The monks old drinking well.");
}

void reset() {
  ::reset();
   if(!present("monk")){
   new(MONKMOBS+"monk2.c")->move(this_object());
   new(MONKMOBS+"monk1.c")->move(this_object());
   }
}
