//      From Maxwell's Underground mudlib
//        9J Room of Dwarf Mining Zone

#include "/adm/include/std.h"
#include "under.h"
inherit "/std/vault";


void reset() {
object mon;
  ::reset();
  if(!present("miner"))
   new("/wizards/maxwell/objects/mon/miner3")->move(this_object());
}
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are standing in an underground room");
    set("long","Test Room2\nMob can leave this room because I have added "
       "door code and kept the set_exits() func." );
   set_exits( ({ "/wizards/maxwell/underzone/test3",
                 "/wizards/maxwell/undezone/test2" }),
            ({ "door","south" }) );
   set_door("door","/wizards/maxwell/underzone/test3", "door",0);
   set_open("door",1);
}

