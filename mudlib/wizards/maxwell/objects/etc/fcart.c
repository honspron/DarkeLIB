//    Maxwell's Underground Mudlib 
//           Dyno Trans Cart

#define UNDER "/wizards/maxwell/underzone/"
inherit "/std/bag_logic";
object *inv;
void create() {
  ::create();
    set_name("mining cart");
    set_id( ({ "mining cart","cart","fcart" }) );
   set_short("an old rusty mining cart" );
    set("long", 
    "This is a large rusty mining cart. It rolls along the mining tracks " 
    "on four large steel wheels. The cart looks like it could hold "
    "a large amount of rocks.\n");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(500);
    inv = ({});
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
    move("/wizards/maxwell/underzone/dm50");
    tell_room(UNDER+"dm50","A large rusty cart rolls into the room.");
}
