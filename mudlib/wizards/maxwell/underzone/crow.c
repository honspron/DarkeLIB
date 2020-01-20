//      From Maxwell's Underground mudlib
//        3rd Room of Dwarf Mining Zone


#include "under.h"
inherit UNDER+"crow2";

void create() {
    ::create();
    set_property("light",0);
    set_property("indoors", 1);
    set("short", "You are standing in a small crow's nest high above the "
        "deck of the ship.");
    set("long", "You are standing in a small crow's nest high above the "
        "deck of the ship.\nYou can see quite a ways from here.");
    set_items( ([
       "crossbeam*" : "The study wooden crossbeams are spaced every few feet under the track.",
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
int no_message(){
    write("You climb down to the ship deck.");
    say(this_player()->query_cap_name()+" climb down onto the ship deck.");
    tell_room(boat_path,this_player()->query_cap_name()+" climb down onto "
     "the ship deck from the crow nest.");
    this_player()->move(boat_path);
    return 0;
}
