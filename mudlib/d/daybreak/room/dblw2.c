#include "../daybreak.h"
inherit "std/room";

void create() {
  ::create();
    set_property("light",3);
    set_property("night light", 2);
    add_exit(ROOMS+"dblw1", "north");
    add_exit(ROOMS+"dblw3","south");
//Basic mapping added by Tiny 1/19/2020
    set("short","   0\n   | \n   @   \n   | \n   0\nLuminous Way");
    set("long","   0\n   | \n   @   \n   | \n   0\nLuminous Way runs north-south through Daybreak Ridge.");
}
