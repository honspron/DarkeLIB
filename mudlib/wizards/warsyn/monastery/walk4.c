#include <std.h>
inherit "std/room";
void reset()
  {
  object mon;
  ::reset();
  if(!present("shadow"))
    new("/wizards/warsyn/monastery/mon/shadow")->move(this_object());
   }
void create()
   {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","Inside the archway. ");
     set("long","The mist clears out here and is replaced with inky " +
           "darkness.   This darkness is alive!  It touches you, probing. " +
           "You can almost hear it whispering to you.  Something is " +
           "wrong here.  Something else is here with you, but where!");
     add_item("darkness","Its moving around you.  Its everywhere " +
            "looking back at you!");
     add_exit("/wizards/warsyn/monastery/walk3","south");
     add_exit("/wizards/warsyn/monastery/walk5","north");
   }
