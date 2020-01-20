#include <std.h>

inherit "std/room";

     void reset()
   {
    object mon;
    ::reset();
    if(!present("guard"))
    new("/wizards/warsyn/monastery/mon/pguard")->move(this_object());
   }

void create() {
     ::create();
     set_property("light", 0);
     set_property("indoors", 1);
     set_property("no castle", 1);
     set("short","Inside the waiting house.");
     set("long","This is the inside of the waiting house." +
           "Once this place held travelers that came here " +
           "seeking prayer. Now the small beds are overturned " +
           "and the foot lockers are all crushed.");
     add_item("lockers","They are all crushed and battered.");
     add_item("beds","Soiled and broken they look terrible.");
     add_exit("/wizards/warsyn/monastery/walk8","out");
     add_exit("/wizards/warsyn/monastery/b2r2","west");
}
