//      From Maxwell's Underground mudlib
//        Test Room 1 of Dwarf Mining Zone

#include <std.h>
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
    set("long", "Test Room 1\nMob cannot be forced to leave or leave on "
        "its own. I'm using\n call miner;force_me;test2\nwith test2 in "
        "quotes to make it a string.");
   set_exits( ({ "/wizards/maxwell/underzone/test2" }),({ "test2" }) );
}

