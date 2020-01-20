//      From Maxwell's Underground mudlib
//        3rd Room of Dwarf Mining Zone


#include "under.h"
inherit BOAT+"crow";

void create() {
    ::create();
    set_property("light",0);
    set_property("indoors", 1);
    set_property("no quit and save", 1);
    set("short", "You are standing in a small crow's nest high above the "
        "deck of the ship.\n");
    set("long", "You are standing in a small crow's nest high above the "
        "deck of the ship.\nYou can see quite a ways from here.\n");
    set_items( ([
       "deck" : "You can see the wooden deck far below.",
       ]) );
       
    set_smell("default", "You can smell the fresh sea breeze.");
    set_listen("default", "You can hear the crashing of the waves.");
    set_pre_exit_functions(({"deck" }), ({"no_message"}) );
}
int add_room(string str,string str2){
    if(!str || !str2)
      return 0;
    if(query_exit(str2) == str)
      return 1;
    else {
      add_exit(str,str2);    
      boat_path = str;
      current_room = str;
    }
    return 1;
}

