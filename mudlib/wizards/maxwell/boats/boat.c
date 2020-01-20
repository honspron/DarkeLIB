// Maxwell's Underground Mudlib 
// Inherited Ship File

#include "under.h"
inherit "/std/bag_logic";

object room,player;
int sail_raised,anchor_raised;
string room_name,target_room;
string *exits,*exit_names,*exit_paths,*exit_returns;
string main_room,*destination,heading,*acpt_heading;
mixed *inv,*linv,grid;
int armour;

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
    add_action("mixed_scanner","navigate");
    add_action("adjust_heading","heading");
    add_action("shell","shell");
    add_action("scanner","scanner");
    room = environment(this_object());    
    acpt_heading = ({"north","south","east","west"});
}
int all_actions(string str2){
string str;
int pos;
object tar_room;

   str = query_verb();
   if(member_array(str,exit_names) != -1 && !str2){
      pos = member_array(str,exit_names);
      write("You head toward the "+str);
      say(this_player()->query_cap_name()+" heads toward the "+str);
      call_other(exit_paths[pos],"add_room",main_room,exit_returns[pos]);
      tar_room = find_object_or_load(exit_paths[pos]);
      tell_room(tar_room,this_player()->query_cap_name()+" enters the "
        +str,this_player());
      if(!find_object(exit_paths[pos])){
         write("Bug! Mail Maxwell");
         return 1;
      }
      this_player()->move(exit_paths[pos]);
      write(exit_paths[pos]->query_long()+"\n"+
            exit_paths[pos]->query_long_exits()+"\n");
      linv = map_array(all_inventory(tar_room),"player_sort",this_object());
      inv = map_array(all_inventory(tar_room),"item_sort",this_object());
      linv = filter_array(linv,"clean_array",this_object());
      inv = filter_array(inv,"clean_array",this_object());
      player = this_player();
      if(sizeof(linv) > 0) 
         write(implode(linv,"\n")+"\n");
      if(sizeof(inv) > 0)
           write(implode(inv,",")+"\n");
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
int adjust_heading(string str){
  if(!str){
    write("The boat has the current heading of "+heading);
    return 1;
  }
  if(member_array(str,acpt_heading) == -1){
    write("Invalid heading. Accepted headings are "
         +implode(acpt_heading,","));
    return 1;
  }
  else {
    heading = str;
    write("You spin the wheel and the boat slowly adjusts. You are "
          "now heading "+heading);
    return 1;
  }
}
//Enter Boat Code
int enter_boat(string str){
    if(str == "ship" || str == "boat") {
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
         this_object()->look_around();
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
    if(str == "ship" || str == "boat") {
     if(this_player()->is_player() || this_player()->is_pet()){
      write("You climb out of the ship");
      say(this_player()->query_cap_name()+" climbs out of the ship.");
      tell_room(environment(this_object()),
      this_player()->query_cap_name()+" climbs out of the ship.");
      this_player()->move(environment(this_object()));
      write(environment(this_object())->query_long()+"\n"+
            environment(this_object())->query_long_exits()+"\n");
      linv=map_array(all_inventory(environment(this_object())),"player_sort",
           this_object());
      inv = map_array(all_inventory(environment(this_object())),"item_sort",
           this_object());
      linv = filter_array(linv,"clean_array",this_object());
      inv = filter_array(inv,"clean_array",this_object());
      player = this_player();
      if(sizeof(linv) > 0) 
         write(implode(linv,"\n")+"\n");
      if(sizeof(inv) > 0)
           write(implode(inv,",")+"\n");
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
           tell_room(environment(this_object()),"Someone on the "
            "deck of the ship raises the sail and it quickly catches the "
            "wind.\n");
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
            tell_room(environment(this_object()),"Suddenly the anchor "
             "rises out of the water and locks into place.\n");
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
           tell_room(environment(this_object()),"Suddenly a large "
            "anchor drops off the side of the ship and splashes into "
            "the waves.\n");
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
           tell_room(environment(this_object()),"Someone on the "
            "deck of the ship lowers the main sail. It quickly folds down "
            "into a large bundle.\n");
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
  if(environment(this_player()) == this_object()){
     if(!str){
       say(this_player()->query_cap_name()+" glances around the deck.");
       write("You are standing on the bow of a huge wooden ship. "
         "The dark polished oak planks stretch out before you broken "
          "only by the mast and the wooden railings.\n");
           player = this_player();
           linv = map_array(all_inventory(this_object()),"player_sort");
           inv = map_array(all_inventory(this_object()),"item_sort");
           linv = filter_array(linv,"clean_array");
           inv = filter_array(inv,"clean_array");
           player = this_player();
       if(sizeof(linv) > 0) 
         write(implode(linv,"\n")+"\n");
       if(sizeof(inv) > 0)
           write(implode(inv,",")+"\n");
       if(sizeof(exit_names) > 1)
           write("There are "+sizeof(exit_names)+" obvious exits: "
           +implode(exit_names,",")+"\n");
       if(sizeof(exit_names) == 1)
           write(" The only obvious exit is "+implode(exit_names,",")+"\n"); 
       return 1;
    }
    if(str == "out"){
      write(environment(this_object())->query_long()+"\n"+
              environment(this_object())->query_long_exits()+"\n");
      say(this_player()->query_cap_name()+" looks out over the side "
            "of the ship.");
      tell_room(environment(this_object()),this_player()->query_cap_name()+
      " looks over the side of the boat and scans the surrounding area.\n");
      player = this_player();
      linv = map_array(all_inventory(environment(this_object())),
            "player_sort");
      inv = map_array(all_inventory(environment(this_object())),
            "item_sort");
      linv = filter_array(linv,"clean_array");
      inv = filter_array(inv,"clean_array");
      player = this_player();
      if(sizeof(linv) > 0) 
         write(implode(linv,"\n")+"\n");
      if(sizeof(inv) > 0)
         write(implode(inv,",")+"\n");
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
      say(this_player()->query_cap_name()+" glances at the anchor.");
      return 1; 
    }
  } 
}
//Misc Func
mixed player_sort(object str){
     if(living(str) && (str != player)){
       if((str->is_player()))      
         return (str->query_title());
       else
         return (str->query_short());
     }
     else
       return 0;
}
mixed item_sort(object str){
   if(!living(str))
      return str->query_short();
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
object troom;
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
      troom = (find_object_or_load(room->query_exit(str)));
      write("You sail toward the "+str+", "+troom->query_short());
      say(this_player()->query_cap_name()+" steers the boat "+str);
      tell_room(room,"The ship breaks the waves and heads "+str);
      move(troom);
      remove_delayed_call("mover");
      tell_room(troom,"A huge boat enters and "
      "breaks the waves as it approaches near you!\n");
      return 1;
    }
    else 
      write("There appears to be land in that direction.");
    return 1;      
}

//Navigation Code
int nav_fun(string str){
object room;
string path,dir,H1,H2,H3;
int Bx,By,Cx,Cy,Tx,Ty;
float dist,angle,nangle;

  destination=({"akkad","mines","kuril","akkad-dock"});
  if(!str || ( member_array(str,destination) == -1) ){
    write("What target location? Possible ones are "+
          implode(destination,","));
    return 1;
  }
  switch(str){
   case "akkad":
    Tx = 15;
    Ty = 15;
   break;
   case "mines":
    Tx = 35;
    Ty = 13;
   break;
   case "kuril":
    Tx = 24;
    Ty = 32;
   break;
   case "akkad-dock":
    Tx = 24;
    Ty = 19;
   break;
  }
  room = environment(this_object());
//  write("Filename of room is "+file_name(room));
  path = file_name(room);
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Bx,By))
    write("The ship is currently at the cords "+Bx+" "+By);
  else {
    write("No cords for this room");
    return 1;
  }
  Cx = (Bx-Tx);
  Cy = (By-Ty);
  dist = sqrt(pow(Cx,2)+pow(Cy,2));
  angle = (asin((By-Ty)/dist)*(180/(3.14)));
  if(Tx > Bx){
     nangle = 90 - angle;
  }
  if(Tx < Bx){
     nangle = 270 + angle;
  } 
  if(Bx == Tx && By < Ty)
     nangle = 180;
  if(nangle > 337.5 || nangle < 22.5)
    dir = "north";
  if(nangle > 22.5 && nangle < 67.5)
    dir = "northeast";
  if(nangle > 67.5 && nangle < 112.5)
    dir = "east";
  if(nangle > 112.5 && nangle < 157.5)
   dir = "southeast";
  if(nangle > 157.5 && nangle < 202.5)
   dir = "south";
  if(nangle > 202.5 && nangle < 247.5)
    dir = "southwest";
  if(nangle > 247.5 && nangle < 292.5)
    dir = "west";
  if(nangle > 292.5 && nangle < 337.5)
    dir = "northwest";  
  H1 = "N";
  H2 = "NE";
  H3 = "NW";
  write("Distance to Target is "+to_int(dist)+" clicks\n"
        "Angle to Target is "+to_int(nangle)+" degrees "+dir);
  return 1;
}
mixed scanner(){
int z,landtype,xline,yline,Bx,By,ypos;
object room,*targets,*inv;
string path;

  room = environment(this_object());
  path = file_name(room);
  inv = all_inventory(room);
  grid = allocate(90);
  write("The current room is "+path+" "+sizeof(all_inventory(room))+"\n");
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Bx,By)){  
//    xline = (Bx-2);
    yline = (By-3);
    targets = ({});    
    while(yline <= (By+3)){
         ypos = 0;
         xline = (Bx-2);
         grid[yline] = allocate(10);
         while(ypos <= 6){ 
              if( (xline >=0 && xline <=40 )&&(yline >= 0 && yline <= 80)){
                room = find_object_or_load("/d/damned/virtual/room_"+
                       xline+"_"+yline+".world");
//                write("The value is "+room->query_short());
                targets = filter_array(inv,"query_boat");
                landtype = (room->query_water());
//                write("X Y pos "+xline+" "+yline+" "+landtype);
                if(landtype == 1){
                  //Water Room
                  if(sizeof(targets) >= 1)
                    grid[yline][ypos] = "*";
                  else
                    grid[yline][ypos] = "#";
                }
                if(landtype == 0){
                   //Land Room
                  if(sizeof(targets) >= 1)
                    grid[yline][ypos] = "L";
                  else
                    grid[yline][ypos] = "!";
                }
                //Check to see if boat room
                if(yline == By && ypos == 2)
                    grid[yline][ypos] = "B";                 
              }
              ypos = ypos + 1;
              xline = xline + 1;
         }      
         yline = yline + 1;
    }
    z = By - 2;
    write("Surface Scan\n");
    while(z <= (By+3) ){
//      write("The size is "+sizeof(grid));
      write(grid[z][0]+" "+grid[z][1]+" "+grid[z][2]+" "+
            grid[z][3]+" "+grid[z][4]+" "+grid[z][5]+" "+
            grid[z][6]);
      z = z + 1;
    }
    write(" * = Target, ! = Land, # = Water, B = Your position");
  }
  return 1;
}
mixed return_grid(){
    return grid;
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
//  Xb = boat x;
//  Yb = boat y;
//  Xt = target x;
//  Xt = target y;
//  Angle is ship heading + 45 degrees 'locked'
//  R is projectile range, default 180 meters
//  50x50 meter room
int shell(string str){
float Xt,Yt,Xb,Yb,Angle,angle,R,Hd;
int z;
object target;
object *inven;
string S;
 if(!str){
   write("Enter X,Y cords,cannon angle off bow,range,cannon side and boat "
         "heading.");
   return 1;
 }
 if(sscanf(str,"%d %d %d %d %s %d",Xb,Yb,angle,R,S,Hd)){
   Hd = (Hd + 90);

   if(S == "left")
    Angle = (Hd + angle)*((3.14)/180);
   else {
    Angle = (Hd - angle)*((3.14)/180); 
    S = "right";
   }
   Xt = Xb + (R*(cos(Angle)));
   Yt = Yb + (R*(sin(Angle)));
   write("Xt and Yt are "+Xt+" "+Yt);
   if(Yt >= (floor(Yt)+0.5))
      Yt = (floor(Yt)+1);
   else
      Yt = floor(Yt);
   if(Xt >= (floor(Xt)+0.5))
      Xt = (floor(Xt)+1);
   else
      Xt = floor(Xt);      
   write("The angle is "+Angle+" on the "+S+" side.");
   write("The shell will land at "+to_int(Xt)+" "+to_int(Yt));
   target = find_object("/d/damned/virtual/room_"+to_int(Xt)+
      "_"+to_int(Yt)+".world");
   tell_room(environment(this_object()),"The cannons on the ship explode into "
     "fire and flames as a cannon flies into the distance!");
   tell_object(this_object(),"The cannons explode into flames!");
   if(target){
     tell_room(target,
       "You hear a loud whistle and can see a dark object falling into "
       "the area around you!\n"
       "BOOOM!!!\n"
       "A huge explosion shakes the ground and sends debris flying!");
     write("Room found and target hit!");
     inven = all_inventory(target);
     z = 0;

     while( z < sizeof(inven) ){
         if(living(inven[z])){
           tell_object(inven[z],"The blast and flying debris rip into your "+
            inven[z]->return_limb()+"!!");
            tell_object(this_object(),inven[z]->query_cap_name()+" was "
            "hit in the blast!");
         }
         else {
             if(inven[z]->query_property("ship") == 1){
                inven[z]->shell_hit();
                write("Your cannon shot hit a boat!");
             }
         }
         z = z+1;
     }
   }
   else
  write("Room not found!");
 }
 else
   write("Enter X,Y cords of boat,cannon angle and projectile range");
 return 1;
}
int shell_hit(){
    if(armour > 0){
       tell_object(this_object(),"The deck of the boat shakes "
       "as a large explosion blows debris in front of you!!");
       tell_room(environment(this_object()),"The ship is rocked "
       "to the side as a large explosion erupts on it!!");
       armour = armour - 1;
    }
     else {
       tell_object(this_object(),"The boat shutters under "
       "the force of another explosion! The hull is breaking "
       "up and sinking fast!");
       tell_room(environment(this_object()),"A large explosion "
       "sends a huge blast wave into the side of the boat! It "
       "takes on water and begins to sink!");
        this_object()->remove();
     }
    return 1;
}
