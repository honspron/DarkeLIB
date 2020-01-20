#include <../daybreak.h>
inherit "std/room";

void create() {
  ::create();
    set_property("light",3);
    set_property("night light", 2);
    add_exit(ROOMS+"dblw2", "north");
    add_exit(ROOMS+"dblw4","south");
    add_exit("/d/damned/guilds/join_rooms/sword-mage_join", "east");
    set("short","Luminous Way");
    set("long","Luminous Way runs north-south through Daybreak Ridge.");
}
