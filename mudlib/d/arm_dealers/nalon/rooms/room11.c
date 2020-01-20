#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"
inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   add_exit(MONKROOMS+"room15", "northwest");
   add_exit(MONKROOMS+"room9", "south");
   set("short","A path");
   set("long",
"This path leads north away from the clearing, and towards "
"a training area belonging to the warrior-monks.  While this "
"part of the village has no living huts, it has no lack of monks "
"travelling to and fro.");
   add_item("training area","The warrior-monks combat training field.");
   add_item("path","The trail leads to the warrior-monks training area.");
}

void reset() {
  ::reset();
   if(!present("monk")){
   new(MONKMOBS+"monk2.c")->move(this_object());
   new(MONKMOBS+"monk1.c")->move(this_object());
   new(MONKMOBS+"monk1.c")->move(this_object());
   }
}
