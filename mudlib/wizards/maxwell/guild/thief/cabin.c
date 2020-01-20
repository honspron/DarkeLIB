//      From Maxwell's Underground mudlib
//        3rd Room of Dwarf Mining Zone

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

int number;
void create() {
    ::create();
    set_property("light",0);
    set_property("indoors", 1);
    set("short", "You are standing in a small mining tunnel.");
    set("long", 
"You are standing in a cluttered ship cabin. Hangin on the walls "
"are picutures of ships and far away lands." 
    );
    set_items( ([
       "crossbeam*" : "The study wooden crossbeams are spaced every few feet under the track.",
       ]) );
       
    set_smell("default", "It smells like a new immortal in here.");
    set_listen("default", "You hear the sounds of code creation.");
}
int add_room(object str){
    add_exit(str,"deck");
    return 1;
}

