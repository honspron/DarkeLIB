//Maxwell's Underground Mudlib
//CrowNest Code

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

string boat_path;
mixed current_room;
object player;

void init() {
    ::init();
    add_action("list_commands","commands");
    add_action("check_horizon","check");
}
int list_commands(string str){
   if(!str){
     write("\n  Commands for Boat Control\n"
          "*****************************\n"
          "'check near','check <dir>'\n"
          "*****************************");
     return 1;
   }
}
int check_horizon(string str){
mixed *inv,*linv,exits,target;
    if(!str){
      write("What do you want to check? Possible locations are "
            "'near' and '<dir>'.");
      return 1;
    }
    if(str == "near"){
       say(this_player()->query_cap_name()+" looks down around the "
         "boat for anything unusual.");
       write("You look down around the boat..\n"+
         environment(find_object(current_room))->query_long()+"\n"+
         environment(find_object(current_room))->query_long_exits()+"\n");
       player= this_player();
       linv = map_array(all_inventory(environment(find_object(current_room))),
                "player_sort");
       linv = filter_array(linv,"clean_array");
       if(sizeof(linv) > 0)
         write("You can see :\n"+implode(linv,","));
       return 1;
    }
    exits = ((environment(find_object(current_room)))->query_exits());
    if(member_array(str,exits) != -1){
      target = ((environment(find_object(current_room)))->query_exit(str) );
      say(this_player()->query_cap_name()+" scans the horizon for anything "
       "unusual.");
      write("You scan the horizen in that direction..\n"+
        (target)->query_long()+"\n"+
        (target)->query_long_exits()+"\n");
      player= this_player();
      linv = 
      map_array(all_inventory(target),"player_sort");
      linv = filter_array(linv,"clean_array");
      if(sizeof(linv) > 0)
        write("You can see :\n"+implode(linv,","));
      return 1;        
    }
    else {
      write("That is not a valid direction.");
      return 1;
    }
}
int no_message(){
    write("You climb down to the ship deck.");
    say(this_player()->query_cap_name()+" climbs down onto the ship deck.");
    tell_room(boat_path,this_player()->query_cap_name()+" climbs down onto "
     "the ship deck from the crowsnest.");
      if(!find_object(boat_path)){
         write("Bug! Boat has been removed, Mail Maxwell");
         return 1;
      }
    this_player()->move(boat_path);
    (boat_path)->look_around();
    return 0;
}
//Misc Func
mixed player_sort(object str){
     if(living(str) && (str != player))             
       return (str->query_cap_name());
     else
       return 0;
}
mixed item_sort(object str){
   if(!living(str))
      return str->query_name();
   else
      return 0;
}
int clean_array(mixed str){
    if(str == 0)
      return 0;
    else
      return 1;
}
