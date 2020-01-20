//    Maxwell's Underground Mudlib 
//           Dyno Trans Cart

#define UNDER "/wizards/maxwell/underzone/"
inherit "/std/bag_logic";
object *inv,*inventory,panel1,panel2,play;
int weight,i,num_rooms_in,num_rooms_out,nro,currently_moving;
string room_name,*rooms_in,*rooms_out,*rooms_in_dir,*rooms_out_dir;

void create() {
  ::create();
    set_name("mining cart");
    set_id( ({ "mining cart","cart","tcart" }) );
    set_short("an old rusty mining cart" );
    set("long", 
    "This is a large rusty mining cart. It looks big enough to hold "
    "a lot of rocks, maybe even an adventurer.\n");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(500);
    inv = ({});
    rooms_in = ({UNDER+"dm72",UNDER+"dm73",UNDER+"dm74",UNDER+"dm71"});
    rooms_out = ({UNDER+"dm9c",UNDER+"dm72",UNDER+"dm73",UNDER+"dm74"});
    rooms_out_dir = ({ "down","down","southeast","east"});
    rooms_in_dir = ({"up","up","northwest","west"});
    num_rooms_in = sizeof(rooms_in);
    num_rooms_out = sizeof(rooms_out); 
    i = 0;
    play = find_player("maxwell");
    currently_moving = 0;
}
void init() {
    add_action("enter_cart","enter");
    add_action("look_around","look");
    add_action("exit_cart","exit");
    add_action("press_lever","press");
}
int enter_cart(string str){
    if(str == "cart") {
      if(this_player()->is_player() || this_player()->is_pet()){
         inventory = all_inventory(this_object());
         if(member_array(this_player(),inventory) != -1){
           write("Your already in the cart!");
           return 1;
         }
         write("You climb into the cart");
         say(this_player()->query_cap_name()+" climbs into the cart.");
         tell_object(this_object(),
              this_player()->query_cap_name()+" climbs into the cart.");
         this_player()->move(this_object()); 
         play = this_player();
         return 1;
      }
     }
}
int press_lever(string str){
    if(str == "lever") {
      if(this_player()->is_player() || this_player()->is_pet()){
         inventory = all_inventory(this_object());
         if(member_array(this_player(),inventory) != -1){
           if(currently_moving == 0){
             write("You press the lever, causing the cart to roll!");
             say(this_player()->query_cap_name()+" presses down on the "
             "lever.");
             this_object()->prepare_move();
             return 1;
           }
           else {
             write("You press the lever, but the brake pad seems to "
                   "be too worn down to stop the cart.");
             say(this_player()->query_cap_name()+" presses down on the "
             "lever, but the brake pad is too worn to stop the cart.");
             return 1;
           }
         }
         write("Your not in the cart!");
         return 1;
      }
     }
}
int exit_cart(string str){
     inventory = all_inventory(this_object());
     if(member_array(this_player(),inventory) != -1){
       if(str == "cart") {
         if(this_player()->is_player() || this_player()->is_pet()){
            write("You climb out of the cart");
            say(this_player()->query_cap_name()+" climbs out of the cart.");
            tell_room(environment(this_object()),
              this_player()->query_cap_name()+" climbs out of the cart.");
            this_player()->move(environment(this_object()));
            return 1;
         }
         write("You not in the cart!");
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
          write("You are in a dirty mine cart used by the miners in the "
          "Under'Drin Mining Complex.\nIf you want to look "
          "outside of the cart, 'look out'.\nTo activate the cart "
          "'press lever'.\nIf you want to leave the cart, 'exit "
          "cart'.\n");

           inv = filter_array(all_inventory(this_object()),(: living :));
           y = sizeof(inv);
           z = 0;
           if(y > 1){
            write("Other Passengers In the Cart");
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
    panel1 = present("panel",find_object(UNDER+"dm71") );
    panel2 = present("panel",find_object(UNDER+"dm9c") );    
    i = 0;
    currently_moving = 1;
    this_object()->mover();
}    
int mover(){    
string sound;
         switch(random(3)){
            case 0: sound = "rumbles";
             break;
            case 1: sound = "clanks";
             break;
            case 2: sound = "creaks";
             break;
         }
//    tell_object(play,"Passing through Mover");
    if(room_name == UNDER+"dm9c"){
//       tell_object(play,"Passing through Mover Part 1A");
       panel1->cart_moving(); 
       panel2->cart_moving();
       if(i < num_rooms_in){       
//         tell_object(play,"Passing through Mover Part 1B");
         tell_room(environment(this_object()),"The cart "+sound+" "
                     +rooms_out_dir[i]+" on the track.");
         tell_room(rooms_in[i],"A cart "+sound+" in from "+rooms_in_dir[i]);
         tell_object(this_object(),"The cart "+sound+" "
                   +rooms_out_dir[i]+" on the track.");
         this_object()->move(rooms_in[i]); 
         i = i + 1;
         call_out("mover",10,this_object());
         return 1;
       }
//       tell_object(play,"Passing through Mover Part 1C");
       tell_room(environment(this_object()),"The cart "+sound+" to a stop "
       "against the blocks.");              
       tell_object(this_object(),"The cart "+sound+" to a stop against the "
       "blocks.");       
       panel1->cart_stopped(); 
       panel2->cart_stopped();
       currently_moving = 0;
    }
    if(room_name == UNDER+"dm71"){
       panel1->cart_moving(); 
       panel2->cart_moving();
       if(nro >= 0){
         tell_room(rooms_out[nro],"A cart "+sound+" in on the "
         +rooms_out_dir[nro]+" track.");
         tell_room(environment(this_object()),"The cart "+sound+" "
                   +rooms_in_dir[nro]+" on the track.");
         tell_object(this_object(),"The cart "+sound+" "
                   +rooms_in_dir[nro]+" on the track.");
         this_object()->move(rooms_out[nro]);
         call_out("mover",10,this_object());
         nro = nro -1;
         return 1;
       }
       tell_room(environment(this_object()),"The cart "+sound+" to a stop "
       "against the blocks.");     
       tell_object(this_object(),"The cart "+sound+" to a stop against the "
       "blocks."); 
       panel1->cart_stopped(); 
       panel2->cart_stopped();
       currently_moving = 0;
    }
}
    
