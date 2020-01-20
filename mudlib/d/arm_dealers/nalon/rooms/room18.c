#include <dirs.h>
#include <std.h>
#include "/d/arm_dealers/nalon/monk.h"
inherit ROOM;

void create() {
  ::create();
   set_property("light",2);
   set_property("indoors",1);
   add_exit(MONKROOMS+"room15", "north");
   set("short","A tent");
   set("long",
"This large old tent, is the headquarters for the warrior "
"monks training program.  Here the important decisions are made "
"by the leaders.  There at mats on which the leaders sit in a "
"circle, not using chairs like the softened more spiritual monks.");
   add_item("tent","A large tent in which the warrior-monks meet.");
   add_item("mats","Small hard mats that the warrior "
"monk leaders use to sit on during there mettings.");
}

void reset() {
  ::reset();
   if(!present("guard")){
      new(MONKMOBS+"monk_guard.c")->move(this_object());
      new(MONKMOBS+"monk_guard.c")->move(this_object());
   }
   if(!present("warrior")){
      new(MONKMOBS+"war_monk1.c")->move(this_object());
      new(MONKMOBS+"war_monk1.c")->move(this_object());
   }
   if(!present("boss"))
      new(MONKMOBS+"monk_boss.c")->move(this_object());
}

