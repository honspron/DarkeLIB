#include "../daybreak.h"
inherit "std/room";

void create() {
  ::create();
    set_property("light",3);
    set_property("night light", 2);
    add_exit(ROOMS+"dbcc4", "east");
    add_exit(ROOMS+"dbcc8","west");
//Basic mapping added by Tiny 1/19/2020
    set("short","   \n    \n0--@--0\n    \n   \nCommerce Court");
    set("long","   \n    \n0--@--0\n    \n   \nCommerce Court runs east-west through Daybreak Ridge.");
}
