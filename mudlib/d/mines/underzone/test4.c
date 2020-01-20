//      From Maxwell's Underground mudlib
//        Test4 Room of Dwarf Mining Zone

#include <std.h>
inherit ROOM;

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are standing in an underground room");
    set("long", "Test Room 1\nMob can be forced to leave or leave on "
        "its own. I'm using set_exits(), but I'm cloning the mob in the "
        "create() instead of the reset().");
   set_exits( ({ "/wizards/maxwell/underzone/test3" }),({ "test3" }) );
   new("/wizards/maxwell/objects/mon/surveyor")->move(this_object());
}

