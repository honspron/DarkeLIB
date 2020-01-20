//      Wizard:  Khojem
//      wood 1
//      wood1.c

#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_property("light", 1);
    set_property("indoors", 0);
    set("short", "Dark woods");
    set("long", "You are closely surrounded by dense wooded growth.  "+
      "The tall, towering trees above block all light to you.  "+
      "There are no signs of a trail or path to guide you through "+
      "this maze of densely wooded growth.  Even if there were a "+
      "trail it would prove hard to follow in this darkness."
    );
    add_exit("wood3","north");
    add_exit("wood2","east");
    add_exit("wood5","west");
    add_exit("wood2","south");
    set_items(([
     ({ "tree","trees", "woods", "growth" }) :
        "The trees are large, healthy trees filled with foliage."+
        "They grow densely all around you.",
     ({ "leaf","leaves" }) :
        "The leaves form a tight, close lattice over your head and don't "
        "allow in any light from above.",
     ({ "trail","path" }) :
        "There is no trail or path to follow!  You are lost."
    ]));
    set_smell("default", "The dank, moist smell of decaying wood is strong "+
      "here.  The smell of... maybe rotting corpses is in the still air."
    );
    set_listen("default", "The silence around you is deafening.  "+
      "Occasionally, you hear sounds of a battle from a ways off.");
}
