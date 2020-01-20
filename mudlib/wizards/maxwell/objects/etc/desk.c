//    Maxwell's Underground Mudlib 
//            Walnut Desk

inherit "/std/bag_logic";
 
void create() {
  ::create();
    set_name("wooden desk");
    set_id( ({ "wooden desk","walnut desk","desk" }) );
   set_short("an old wooden desk" );
  set("long", "This desk is made from high quality walnut wood. There are "
   "several drawers along the side of the desk.");
    set_weight(100000);
    set_value(0);
    set_possible_to_close(1);
    set_max_internal_encumbrance(500);
    toggle_closed();
    set_lock("locked");
    set_key("fenton key");
}

