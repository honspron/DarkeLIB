#include <std.h>

inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","A walkway");
     set("long","It is hard to see now. The mist here is dense " +
           "and pulses with life. Small lights arc back and forth " +
           "in the mist as lightening would in a cloud bank. The " +
           "walkway is barely visible beneath you.");
     add_item("mist","Looking into the mist it seems to clear " +
                    "up  for a moment then returns to its normal " +
                    "density");
     add_item("lights","The lighs look like small bolts of " +
                    "lightening. They give the mist an appearance " +
                    "of life.");
     add_item("walkway","You cant see any of the walkway " +
                    "except for the places where the footprints are.");
     add_item("footprints","Here the footprints sparkle with " +
                    "the same light that moves in the mist.");
     add_exit("/wizards/warsyn/monastery/walk1","south");
     add_exit("/wizards/warsyn/monastery/walk3","north");
}
