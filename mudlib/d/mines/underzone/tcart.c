//    Maxwell's Underground Mudlib 
//           Dyno Trans Cart

#define UNDER "/wizards/maxwell/underzone/"
inherit "/std/bag_logic";
object *inv,*inventory;
int weight;
void create() {
  ::create();
    set_name("mining cart");
    set_id( ({ "mining cart","cart","fcart" }) );
   set_short("an old rusty mining cart" );
    set("long", 
    "This is a large rusty mining cart. It looks big enough to hold "
    "a lot of rocks, maybe even an adventurer.\nTo activate the cart"
    "pull the lever.");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(500);
    inv = ({});
}
void init() {
    add_action("enter_cart","enter");
    add_action("look_around","look");
    add_action("exit_cart","exit");
    add_action("pull_lever","pull");
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
         this_player()->move(this_object()); 
         return 1;
      }
     }
}
int pull_lever(string str){
    if(str == "lever") {
      if(this_player()->is_player() || this_player()->is_pet()){
         inventory = all_inventory(this_object());
         if(member_array(this_player(),inventory) != -1){
           write("You pull the lever, causing the cart to roll!");
           say(this_player()->query_cap_name()+" pulls back on the lever.");
           return 1;
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
      inventory = all_inventory(this_object());
      if(member_array(this_player(),inventory) != -1){
        if(str == 0){
          write("You are in a dirty mine cart. If you wanted to look "
          "outside of the cart, you could 'look out'");
          return 1;
        }
        if(str == "out"){
          write(environment(this_object())->query_long()+"\n"+
                environment(this_object())->query_long_exits());
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
      inv[z]->move(environment(this_object()));
      z = z + 1;
    }
    tell_room(here,"The cart begins to move and rolls into the south "
    "tunnel");
    if(file_name(here) == (UNDER+"dm9c")){
      move(UNDER+"dm71");
      tell_room(UNDER+"dm71","A large rusty cart rolls into the room.");
    }
    if(file_name(here) == (UNDER+"dm71")){
      move(UNDER+"dm9c");
      tell_room(UNDER+"dm9c","A large rusty cart rolls into the room.");
    }
}
