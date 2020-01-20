//Maxwell's Underground MudLib
//Moving Mine Cart
//Coded For DarkeMud
//@Copyright 1996

#include "/adm/include/std.h"
#define MPATH "/wizards/maxwell/underzone/dm"
inherit "/std/bag_logic";

int current_room,rsize,num,y,z;
string *room,*cin_mess,*nin_mess,fname,mode,cstatus;
object here,cart,*inv;

void create(){
    set_id( ({"cart"}) );
    set_name("cart");
    set("short", "a large mining cart");
    set_weight(300000);
    set("long", 
    "This is a large rusty mining cart. It rolls along the mining tracks " 
    "on four large steel wheels. The cart looks like it could hold "
    "a large amount of rocks.\nThere is a large lever on the side.");
    set_value(50);
    set_max_internal_encumbrance(5000);
    room = ({MPATH+"2",MPATH+"3",MPATH+"4",MPATH+"5",MPATH+"6",MPATH+"8",
            MPATH+"9b",MPATH+"9d",MPATH+"62",MPATH+"63",MPATH+"64",
            MPATH+"65",MPATH+"66"});
    cin_mess=({"northwest","northwest","southwest","southwest","southwest",
             "south","southwest","west","west","west","west","west"});
    nin_mess=({"southeast","southeast","northeast","northeast","northeast",
             "north","northeast","east","east","east","east","east"});
    inv = ({});
    rsize = sizeof(room);
    cart = this_object();
    cstatus = "stopped";
}
void init() {
    ::init();
    add_action("pull", "pull");
    add_action("look_lever","look");
}
int look_lever(string str){
    if(str == "lever" || str == "at lever"){
      write("The long steel lever looks like it can be pulled to "
            "operate the cart.");
      say(this_player()->query_cap_name()+" looks at the lever on the "
         "cart.");
      return 1;
    }
}
int pull(string str){
   if(cstatus == "stopped" && str = "lever"){
     write("You pull back on the lever");
     cstatus = "moving";
    fname = file_name(environment(cart));
    current_room = member_array(fname,room);
    num = rsize - 1;
     if(current_room == 0 || current_room == num ){
          if(current_room == 0) mode = "in";
          else
             mode = "out";
      }
     else {
       switch(random(2)){
         case 0: mode = "in";
           break;
         case 1: mode = "out";
           break;
       }
     }
     call_out("mover",5,this_object());
     return 1;
   }
   if(cstatus == "moving" && str == "lever"){
    here = environment(cart);
    write("You pull the lever foward"); 
    tell_room(here,"The cart creaks to a stop.");
    cstatus = "stopped";
    return 1;
    }
   return 0;
}
int mover(){    
    fname = file_name(environment(cart));
    current_room = member_array(fname,room);
    num = rsize - 1;
    if(current_room == 0 || current_room == num ){
       if(current_room == 0){
         mode = "in";          
         inv = all_inventory(cart);
         y = sizeof(inv);
         z = 0;
         if(y == 0)tell_room(fname,"The cart tilts up, but it is empty.");
         if(y > 0)tell_room(fname,"The cart tilts up and dumps its contents "
         "on the ground.");
         while(z <=(y-1)){
            inv[z]->move(environment(cart));
            z = z + 1;
          }
       }
       if(current_room == num) mode = "out";          
    }
    if(mode == "in" && current_room != -1 && cstatus == "moving"){
      tell_room(fname,"The cart rolls "+cin_mess[current_room]);      
      cart->move(room[current_room + 1]);
      tell_room(room[current_room + 1],"A cart rolls in from the "
          +nin_mess[current_room]);
      call_out("mover",5,this_object());
    }
    if(mode == "out" && current_room != -1 && cstatus == "moving"){
      tell_room(fname,"The cart rolls "+nin_mess[current_room - 1]);      
      cart->move(room[current_room - 1]);
      tell_room(room[current_room - 1],"A cart rolls in from the "
          +cin_mess[current_room - 1]);
      call_out("mover",5,this_object());
    }
    if(current_room == -1)
       tell_room(fname,"There is no track for the cart to ride on.");
    return 1;
}

