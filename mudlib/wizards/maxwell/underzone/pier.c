
//Inherited Dock Code

inherit ROOM;
#include "/adm/include/std.h"
#include "under.h"

void init() {
    ::init();
    add_action("create_boat","create");
    add_action("save_boat","sboat");
    add_action("load_boat","load");
}

int create_boat(string str){
object *boats,boat;
int z,value,lround,mround,hround;
string name;

  if((str == "boat" || str == "ship") && (this_user()->is_player()) ){
    boats = children("/wizards/maxwell/boats/ship");

    while(z < sizeof(boats)){
      if(boats[z]->query_property("owner") == getuid(this_user())){
        write("Records show you already own a boat and it's in use.");
        return 1;
      }
      z=z+1;
    }
    if(file_exists(UNBOAT+"data/"+getuid(this_user())+".o")){
       write("Records show you already own a boat. Use 'load boat' "
             "to access your ship.");
       return 1;
    }
    write("The price of the boat is 25 Mithril.\n"
          "Checking your available funds...");
    if(this_user()->query_money("mithril") < 25){
       write("You don't have enough Mithril to buy a boat.");
       return 1;
    }
    this_user()->add_money("mithril",-25);
    write("Your creation fee is now paid. Your boat is now available "
            "at any time. To load the boat in the future just "
            "come to the dock and use 'load ship'.\n"
           "Keep in mind that you can currently own only 1 boat and "
           "you do not have to save the boat in order to use it later.\n"
           "Please mail any bug reports to Maxwell and be sure to "
           "check out\n'help boats' and "
           "'commands' once you are aboard "
           "your ship.\n");           
    boat = new("/wizards/maxwell/boats/ship");
    boat->move(this_object());
    name = getuid(this_user());
    value = boat->query_property("value");
    lround = 15;
    mround = 15;
    hround = 15;
    boat->set_property("owner",name);
    boat->set_property("light_powder",lround);
    boat->set_property("medium_powder",mround);
    boat->set_property("heavy_powder",hround);
    boat->save_me(name);

    tell_room(this_object(),"The wind whistles silently as the dock "
              "hands push a new boat into the water.");
    write_file(UNBOAT+"data/log",name+" "+ctime(time())+"\n");
    return 1;
  }
}
int query_water(){
    return 1;
}
int save_boat(string str){
string name;
int value;
object boat;
 if(str == "boat"){
   name  = getuid(this_user());
   value = boat->query_property("value");
   write_file(UNBOAT+"data/"+name+".o","owner "+name+" value "+value,1);
   message("info","Boat saved!");
   return 1;
 }
}

int load_boat(string str){
string name,info,owner;
int value,z,lround,mround,hround;
object boat,*boats;

 if(str == "boat" || str == "ship"){
   name  = getuid(this_user());
   info = (UNBOAT+"data/"+name+".o");
   if(!file_exists(info)){
     message("info","There is no mention of your boat in our records.",
             this_user());
     return 1;
   }
   boats = children("/wizards/maxwell/boats/ship");
   while(z < sizeof(boats)){
     if(boats[z]->query_property("owner") == getuid(this_user())){
        message("info","Our records show your boat is not in the storage "
                "bay and is probably in use.",this_user());
        return 1;
     }
     z=z+1;
   }
   message("info","Evaluating your boat record now and preparing for "
           "loading.",this_user());
   boat = new("/wizards/maxwell/boats/ship.c");
   boat->restore_me(name);
   boat->move(this_object());
   message("info","The dock hands push your boat out into the water.",
             this_user());
   return 1;
 }
}  
