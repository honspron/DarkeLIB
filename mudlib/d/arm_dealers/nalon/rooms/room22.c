#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"
inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   set_property("indoors",1);
   add_exit(MONKROOMS+"room20", "north");
   set("short","A hut");
   set("long",
"This is the living quarters of a monk, the hut is large "
"and well furnished.  A large bed lies in the back of the room, "
"surprisingly bare.  This hut belongs to a spiritual monk "
"The air is filled with the smell of an insense, burned "
"to help the monk meditate.");
   add_item("bed","A large bed pushed up against the back wall");
   set_smell("default","The scent of insense hangs in the air");
}
void reset() {
  ::reset();
   if(!present("monk")){
   new(MONKMOBS+"monk2.c")->move(this_object());
   new(MONKMOBS+"monk3.c")->move(this_object());
   new(MONKMOBS+"monk1.c")->move(this_object());
   new(MONKMOBS+"monk_woman.c")->move(this_object());
   }
}
