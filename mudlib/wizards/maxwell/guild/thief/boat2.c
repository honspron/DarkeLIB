// Maxwell's Underground Mudlib 
// Inherited Ship File

#include "under.h"
inherit "/std/bag_logic";

object room,player;
int sail_raised,anchor_raised;
string room_name,target_room;
string *exits,*exit_names,*exit_paths,*exit_returns;
string main_room;

void init() {
    ::init();
    add_action("list_commands","commands");
    add_action("enter_boat","enter");
    add_action("exit_boat","exit");
    add_action("look_around","look");
    add_action("raise_sail_anchor","raise");
    add_action("lower_sail_anchor","lower");   
    add_action("move_boat","sail");
    add_action("all_actions","");
    room = environment(this_object());    
}
int all_actions(string str2){
string str;
int pos;
   str = query_verb();
   if(member_array(str,exit_names) != -1 && !str2){
      pos = member_array(str,exit_names);
      write("You head toward the "+str);
      say(this_player()->query_cap_name()+" heads toward the "+str);
      this_player()->move(exit_paths[pos]);
      call_other(exit_paths[pos],"add_room",main_room,exit_returns[pos]);
      return 1;
   }
}
//Command List Code
int list_commands(string str){
   if(!str){
     write("\n  Commands for Boat Control\n"
          "*****************************\n"
          "'raise sail','lower sail'\n"
          "'raise anchor','lower anchor'\n"
          "'sail <dir>','look out'\n"
          "'exit ship'\n"
          "*****************************");
     return 1;
   }
}

//Enter Boat Code
int enter_boat(string str){
    if(str == "ship") {
      if(this_player()->is_player() || this_player()->is_pet()){
         if(environment(this_player()) == this_object()){
           write("You're already in the ship!");
           return 1;
         }
         write("You climb into the ship");
         say(this_player()->query_cap_name()+" climbs into the ship.");
         tell_object(this_object(),
              this_player()->query_cap_name()+" climbs into the ship.");
         this_player()->move(this_object()); 
         return 1;
      }
     }
}

//Exit Boat Code
int exit_boat(string str){
     if(environment(this_player()) != this_object())
        return 0;
     if(!str){
       write("Exit what?");
       return 1;
     }      
     if(str == "ship") {
       if(this_player()->is_player() || this_player()->is_pet()){
         write("You climb out of the ship");
         say(this_player()->query_cap_name()+" climbs out of the ship.");
         tell_room(environment(this_object()),
            this_player()->query_cap_name()+" climbs out of the ship.");
         this_player()->move(environment(this_object()));
         return 1;
       }
     }
}

//Raise Sail or Anchor Code
int raise_sail_anchor(string str){
    if(str == "sail" || str == "anchor") {
      if(this_player()->is_player() || this_player()->is_pet()){
        if(environment(this_player()) != this_object())
           return 0;
        if(str == "sail"){
          if(sail_raised == 0){
           write("You raise the sail and it quickly catches the wind");
           say(this_player()->query_cap_name()+" raises the sail and "
           "the boat begins to move!");
           if(anchor_raised)
            remove_delayed_call("mover"); 
            this_object()->prepare_move();
           sail_raised = 1;
          }
          else {
           write("The sail is already raised!");
           say(this_player()->query_cap_name()+" tries to adjust the "
              "sail but then realizes that it is already raised.");
          }          
          return 1;
        }
        if(str == "anchor"){
          if(anchor_raised == 0){
            write("You raise the anchor and the boat begins to drift!");
            say(this_player()->query_cap_name()+" raises the anchor "
              "and the boat begins to drift.");            
            remove_delayed_call("mover");
            anchor_raised = 1;
            this_object()->prepare_move();
          }
          else {
           write("The anchor is already raised!");
           say(this_player()->query_cap_name()+" tries to raise the "
            "anchor but then realizes it is already raised.");
          }
          return 1; 
        }
      }
   }
}

//Lower Sail or Anchor Code
int lower_sail_anchor(string str){
    if(str == "anchor" || str == "sail") {
      if(this_player()->is_player() || this_player()->is_pet()){
        if(environment(this_player()) != this_object())
           return 0;
       if(str == "anchor"){
         if(anchor_raised == 1){
           write("You lower the anchor and it clatters into the murky waves. "
            "The boat slowly drifts to a stop.");
           say(this_player()->query_cap_name()+" lowers the anchor "
              "and it splashes into the waves. The boat slowly drifts "
              "to a stop.");
           remove_delayed_call("mover");
           anchor_raised = 0;
         }
         else {
           write("The anchor is already lowered.");
           say(this_player()->query_cap_name()+" tries the lower "
              "the anchor but then realizes it already is.");             
         }
         return 1;
      }
      if(str == "sail"){
        if(sail_raised == 1){
          write("You lower the sail and tie it down.");
          say(this_player()->query_cap_name()+" lowers the sail and "
             "ties it down.");
          sail_raised = 0;
          remove_delayed_call("mover");
          this_object()->prepare_move();
        }
        else {
          write("The sail is already lowered.");
          say(this_player()->query_cap_name()+" tries to lower the "
            "sail but realizes it is already been lowered.");
       }
       return 1;
      }
     }
   }
}          

//Look at Boat Code
int look_around(string str){     
int y,z;
mixed *inv,*linv;
      if(environment(this_player()) == this_object()){
        if(!str){
          write("You are standing on the bow of a huge wooden ship. "
          "The dark polished oak planks stretch out before you broken "
          "only by the mast and the wooden railings.\n");
           player = this_player();
           linv = map_array(all_inventory(this_object()),"player_sort");
           inv = map_array(all_inventory(this_object()),"item_sort");
           linv = filter_array(linv,"clean_array");
           inv = filter_array(inv,"clean_array");
           if(sizeof(linv) > 0) 
            write("Other Passengers In the Ship:\n"+implode(linv,",")+"\n");
           if(sizeof(inv) > 0)
            write("Items in Ship:\n"+implode(inv,",")+"\n");
           if(sizeof(exit_names) > 0)
             write("Possible Exits:\n"+implode(exit_names,",")+"\n");
           return 1;
        }
        if(str == "out"){
          write(environment(this_object())->query_long()+"\n"+
              environment(this_object())->query_long_exits()+"\n");
          player = this_player();
          linv = map_array(all_inventory(environment(this_object())),
                "player_sort");
          linv = filter_array(linv,"clean_array");
          if(sizeof(linv) > 0)
            write("You can see :\n"+implode(linv,","));
          return 1;
        }
        if(str == "sail"){
          if(sail_raised)
             write("The leather sail has been raised.");
          else
              write("The leather sail is tied down on the mast.");
          say(this_player()->query_cap_name()+" glances at the sail.");
          return 1;
        }
        if(str == "anchor"){
           if(anchor_raised)
             write("The black chain anchor is raised and locked in place.");
           else
             write("The black chain anchor has been lowered into the "
                   "murky water.");
           return 1; 
        }
      } 
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
//Moving Code Part 1
int prepare_move(){
    room_name = file_name(environment(this_object()));
    exits = filter_array(room_name->query_exits(),"sea_exits");
    if(anchor_raised == 0)
      return 1;
    if(sail_raised)
     delayed_call("mover",15);
    else
     delayed_call("mover",45);
}    

//Moving Code Part 2
int mover(){    
string sound;
int i;
   switch(random(3)){
          case 0: sound = "floats";
          break;
          case 1: sound = "moves";
          break;
          case 2: sound = "flows";
          break;
   }
   i = random(sizeof(exits));
   target_room = (room_name->query_exit(exits[i]));       
   tell_room(environment(this_object()),"The boat "+sound+" "
        +exits[i]+" on the water.");
   tell_room(target_room,"A boat "+sound+" in from "+exits[i]);
   tell_object(this_object(),"The boat "+sound+" "+exits[i]+" on the water.");
   this_object()->move(target_room); 
   this_object()->prepare_move();
   return 1;
}

//Sailing Code
int move_boat(string str){
  if( living(environment(this_object())) ||
      (environment(this_player()) != this_object()) )
        return 0;   
  room = environment(this_object());
  exits=filter_array(environment(this_object())->query_exits(),"sea_exits");
  if(!str){
    write("Which way do you want to sail? Possible directions are "
      +implode(exits,",")+".");
      return 1;
    }
    if(member_array(str,exits) == -1){
      write("You can't sail in that direction. Possible directions are "
      +implode(exits,",")+".");
      return 1;
    }
    if(sail_raised == 0){
      write("The sail is down.");
      return 1;
    }
    if(anchor_raised == 0){
      write("The anchor is still down!");
      return 1;
    }
    if(find_object_or_load(room->query_exit(str))->query_water()){
      write("You sail "+str+", "+room->query_short());
      say(this_player()->query_cap_name()+" steers the boat "+str);
      move(find_object_or_load(room->query_exit(str)));
      remove_delayed_call("mover");
      tell_room(find_object_or_load(room->query_exit(str)),"A huge boat "
       "sails breaks the waves as it approaches near you!\n");
      return 1;
    }
    else 
      write("There appears to be land in that direction.");
    return 1;      
}

//Misc Func
int sea_exits(string str){
    room = environment(this_object());
    if(find_object_or_load(room->query_exit(str))->query_water())
      return 1;
    else
      return 0;
}

//Misc Func
object query_info(){
    return room;
}

