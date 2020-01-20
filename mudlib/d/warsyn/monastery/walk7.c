#include <std.h>

inherit "std/room";

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","Doorway to pilgrim waiting house.");
     set("long","The building was once used to house pilgrims that " +
           "traveled here for prayers. It also served to hold young " +
           "would be initiates. The building streches far to the east. ");
     add_item("building","This building was once whitelong ago.  ");
     add_exit("/wizards/warsyn/monastery/walk6","west");
     add_exit("/wizards/warsyn/monastery/b1r1","enter");
}
