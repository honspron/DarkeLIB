//      from the Nightmare mudlib
//      an example workroom for new immortals

#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "This is the guest room.");
    set("long", "You are stuck here, deal with it or make a character.");
}
