#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"

inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   add_exit(MONKROOMS+"room26", "west");
   set("short","Meditation area");
   set("long",
"This is where peaceful monks come to relax and "
"meditate.  A soft grassy area has been cleared out "
"for them to sit while they ponder the meaning of life. "
"To the west is a fire pit.");
   add_item("pit","A large fire pit in which the monks "
"burn special materials with there wood, to help expand "
"there minds.");
   add_item("fire pit","A large fire pit in which the monks "
"burn special materials with there wood, to help expand "
"there minds.");
   add_item("area","A soft patch of grass to keep the monks "
"comfortable while they meditate.");
}

void reset() {
  ::reset();
   if(!present("monk")){
   new(MONKMOBS+"med_monk.c")->move(this_object());
   new(MONKMOBS+"med_monk.c")->move(this_object());
   new(MONKMOBS+"med_monk.c")->move(this_object());
   }
}
