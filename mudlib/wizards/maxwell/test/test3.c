//      From Maxwell's Underground mudlib
//      3rd Test Room

#include "/adm/include/std.h"
inherit ROOM;

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
    set("long", "Test Room3\nMob can move because I'm now using add_exit() "
       "instead of set_exits()." );
    add_exit("/wizards/maxwell/underzone/test2","south");
    add_exit("/wizards/maxwell/underzone/test4","north");
}

