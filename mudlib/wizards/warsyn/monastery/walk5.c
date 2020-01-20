#include <std.h>

inherit "std/room";

void create() {
     ::create();
     set_property("light", 1);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 0);
     set("short","A small courtyard.");
     set("long","You are in a small courtyard. Behind you is a " +
           "writhing darkness covering the archway.  The air here   " +
           "is heavy with moisture and foul smoke. This place leaves " +
           "a bad taste in your mouth. Then you realize the taste is " +
           "burned flesh. The ground beneath your feet is soft. The " +
           "path here is destroyed.");
     add_item("path","It is nothing more than rubble now.");
     add_item("archway","Dark shadows move all around the archway.");
     add_exit("/wizards/warsyn/monastery/walk4","south");
     add_exit("/wizards/warsyn/monastery/walk6","north");
}
