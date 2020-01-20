//    Maxwell's Underground Mudlib 
//           Dyno Trans Cart

#include "under.h"
inherit "/std/bag_logic";

object *inv,*inventory,panel1,panel2,play;
int weight,i,num_rooms_in,num_rooms_out,nro,currently_moving;
string room_name,*rooms_in,*rooms_out,*rooms_in_dir,*rooms_out_dir;

void create() {
  ::create();
    set_name("thief boat");
    set_id( ({ "thief boat","boat" }) );
    set_short("an old wooden boat" );
    set("long", 
    "This is a large wooden boat. It looks big enough to hold "
    "a lot of equipment, maybe even a couple of adventurers.\n");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(500);
    inv = ({});
    rooms_in = ({UNTHIEF+"thief11",UNTHIEF+"thief12",UNTHIEF+"thief13"});
    rooms_out = ({UNTHIEF+"thief10",UNTHIEF+"thief11",UNTHIEF+"thief12"});
    rooms_out_dir = ({ "down","down","southeast"});
    rooms_in_dir = ({"up","up","northwest"});
    num_rooms_in = sizeof(rooms_in);
    num_rooms_out = sizeof(rooms_out); 
    i = 0;
    play = find_player("maxwell");
    currently_moving = 0;
}
void init() {
    add_action("enter_boat","enter");
    add_action("look_around","look");
    add_action("exit_boat","exit");
    add_action("raise_sail","raise");
}
int enter_boat(string str){
    if(str == "boat") {
      if(this_player()->is_player() || this_player()->is_pet()){
         inventory = all_inventory(this_object());
         if(member_array(this_player(),inventory) != -1){
           write("Your already in the boat!");
           return 1;
         }
         write("You climb into the boat");
         say(this_player()->query_cap_name()+" climbs into the boat.");
         tell_object(this_object(),
              this_player()->query_cap_name()+" climbs into the boat.");
         this_player()->move(this_object()); 
         play = this_player();
         return 1;
      }
     }
}
int raise_sail(string str){
    if(str == "sail") {
      if(this_player()->is_player() || this_player()->is_pet()){
         inventory = all_inventory(this_object());
         if(member_array(this_player(),inventory) != -1){
           if(currently_moving == 0){
             write("You raise the sail and it quickly catches the wind "
               "rushing through the tunnel. The rudder automatically "
               "adjusts and the boat begins to move!");
             say(this_player()->query_cap_name()+" raises the sail and "
             "the boat begins to move!");
             this_object()->prepare_move();
             return 1;
           }
           else {
             write("You try to adjust the sail, but the boat doesn't "
                  "respond.");
             say(this_player()->query_cap_name()+" tries to adjust the "
             "sail but the boat continues on.");
             return 1;
           }
         }
         write("Your not in the boat!");
         return 1;
      }
     }
}
int exit_boat(string str){
     inventory = all_inventory(this_object());
     if(member_array(this_player(),inventory) != -1){
       if(str == "boat") {
         if(this_player()->is_player() || this_player()->is_pet()){
            write("You climb out of the boat");
            say(this_player()->query_cap_name()+" climbs out of the boat.");
            tell_room(environment(this_object()),
              this_player()->query_cap_name()+" climbs out of the boat.");
            this_player()->move(environment(this_object()));
            return 1;
         }
         write("You not in the boat!");
         return 1;
       }
       write("Exit what?");
       return 1;
     }

}
int look_around(string str){     
int y,z;
object *inv;
      inventory = all_inventory(this_object());
      if(member_array(this_player(),inventory) != -1){
        if(str == 0){
          write("You are in a dirty wooden boat used by the members of the "
          "ancient temple\nIf you want to look "
          "outside of the boat, 'look out'.\nTo use the boat "
          "'raise sail'.\nIf you want to leave the boat, 'exit "
          "boat'.\n");

           inv = filter_array(all_inventory(this_object()),(: living :));
           y = sizeof(inv);
           z = 0;
           if(y > 1){
            write("Other Passengers In the Boat");
            while(z <=(y-1)){
              if(inv[z] != this_player())
                 write(inv[z]->query_short());
              z = z + 1;
            }
           }

          return 1;
        }
        if(str == "out"){
          write(environment(this_object())->query_long()+"\n"+
              environment(this_object())->query_long_exits()+"\n");
          return 1;
        }
        write("You do not notice that here.");
        return 1;
      }
}
int empty(){
int y,z;
object here;
    here = environment(this_object());
    inv = all_inventory(this_object());
    y = sizeof(inv);
    z = 0;
    if(y == 0)tell_room(here,"The cart tilts up, but it is empty.");
    if(y > 0)tell_room(here,"The cart tilts up and dumps its contents on "
    "the ground.");
    while(z <=(y-1)){
      tell_object(inv[z],"The cart tilts up and you tumble out onto the "
                         "floor!");
      inv[z]->move(environment(this_object()));
      z = z + 1;
    }
    this_object()->prepare_move();
}
int prepare_move(){
    room_name = file_name(environment(this_object()));
    nro = num_rooms_out - 1;
//    panel1 = present("panel",find_object(UNDER+"dm71") );
//    panel2 = present("panel",find_object(UNDER+"dm9c") );    
    i = 0;
    currently_moving = 1;
    this_object()->mover();
}    
int mover(){    
string sound;
         switch(random(3)){
            case 0: sound = "floats";
             break;
            case 1: sound = "moves";
             break;
            case 2: sound = "flows";
             break;
         }
    if(room_name == UNTHIEF+"thief10"){
//       panel1->cart_moving(); 
//       panel2->cart_moving();
       if(i < num_rooms_in){       
         tell_room(environment(this_object()),"The boat "+sound+" "
                     +rooms_out_dir[i]+" on the water.");
         tell_room(rooms_in[i],"A boat "+sound+" in from "+rooms_in_dir[i]);
         tell_object(this_object(),"The boat "+sound+" "
                   +rooms_out_dir[i]+" on the water.");
         this_object()->move(rooms_in[i]); 
         i = i + 1;
         call_out("mover",10,this_object());
         return 1;
       }
//       tell_object(play,"Passing through Mover Part 1C");
       tell_room(environment(this_object()),"The boat "+sound+" against the "
       "dock and stops.");              
       tell_object(this_object(),"The boat "+sound+" against the "
       "dock and stops.");       
//       panel1->cart_stopped(); 
//       panel2->cart_stopped();
       currently_moving = 0;
    }
    if(room_name == UNTHIEF+"thief13"){
//       panel1->cart_moving(); 
//       panel2->cart_moving();
       if(nro >= 0){
         tell_room(rooms_out[nro],"A boat "+sound+" in from the "
         +rooms_out_dir[nro]);
         tell_room(environment(this_object()),"The boat "+sound+" "
                   +rooms_in_dir[nro]+" on the river.");
         tell_object(this_object(),"The boat "+sound+" "
                   +rooms_in_dir[nro]+" on the river.");
         this_object()->move(rooms_out[nro]);
         call_out("mover",10,this_object());
         nro = nro -1;
         return 1;
       }
       tell_room(environment(this_object()),"The boat "+sound+" to a stop "
       "against the blocks.");     
       tell_object(this_object(),"The boat "+sound+" to a stop against the "
       "blocks."); 
//       panel1->cart_stopped(); 
//       panel2->cart_stopped();
       currently_moving = 0;
    }
}
    
