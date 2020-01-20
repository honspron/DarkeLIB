#include <std.h>

inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","A walkway ");
     set("long","You have found a walkway made of a strange  " +
          "white stone. A fine mist hovers at your feet slowly " +
          "drifting north on a wind you do not feel. An odd sense " +
          "of peace hangs in the air around you. ");
     add_item("mist","This mist hovers and moves on its own " +
                    "accord. It lightly drifts between your feet moving " + 
                    "north.");
     add_item("walkway","The walkway seems to be carved " +
                    "from a single piece of stone. It is pure white and " +
                    "unbroken except for footprints leading north.");
     add_item("footprints","Something passing here cracked " +
                    "the stone as it walked leaving footprints.");
     add_exit("/wizards/warsyn/monastery/walk2","north");
     add_exit("/wizards/warsyn/workroom","south");
}
