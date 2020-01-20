//      From Maxwell's Underground mudlib
//        3rd Room of Dwarf Mining Zone

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

int number;
string boat_path;

void create() {
    ::create();
    set_property("light",0);
    set_property("indoors", 1);
    set("short", "You are standing in a small mining tunnel.");
    set("long", 
"You are standing in a cluttered ship cabin. Hangin on the walls "
"are picutures of ships and far away lands.\n" 
    );
    set_items( ([
       "crossbeam*" : "The study wooden crossbeams are spaced every few feet under the track.",
       ]) );
       
    set_smell("default", "It smells like lamp oil and old maps.");
    set_listen("default", "You hear the sounds of the sea.");
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
    }
    return 1;
}
int no_message(){
    write("You step onto the ship deck.");
    say(this_player()->query_cap_name()+" steps out onto the ship deck.");
    tell_room(boat_path,this_player()->query_cap_name()+" walks out onto "
     "the ship deck from the cabin.");
    this_player()->move(boat_path);
    return 0;
}
