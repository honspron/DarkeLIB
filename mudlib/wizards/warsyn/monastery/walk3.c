#include <std.h>

inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","A walkway");
     set("long","From out of the mist an enormous archway " +
           "rises before you. It is made of the same material " +
           "as the walkway. The mist still creates a haze blocking " +
           "your view ahead.");
     add_item("mist","Its all around you now. When you are not " +
                    "looking the mist seems to close in on you");
     add_item("archway","This is an enormous archway made " +
                     " of a pure white stone. Near the bottom of the " +
                      "archway the stone seems to shimmer");
     add_item("walkway","The walkway is easier to see here. " +
                     " The stone is unbroken by the footprints that " +
                      "you had seen before.");
     add_item("shimmer","Here the perfect master walked. " +
                     "His bare feet cracked the stone as he approached . " +
                     "This path is known as the path of  enlightenment. " +
                     "Beyond the archway the monks preserve His work.");
     add_exit("/wizards/warsyn/monastery/walk2","south");
     add_exit("/wizards/warsyn/monastery/walk4","north");
}
