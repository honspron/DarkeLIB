//    Maxwell's Underground Mudlib 
//          Silver Altar of Axe of Dulith
inherit "/std/bag_logic";

int z; 
string here;
void create() {
  ::create();
    set_name("altar");
    set_id( ({ "altar" }) );
   set_short("a silver altar" );
    set_long("The altar is made of solid silver with encrusted "
"gems spread across its surface. The middle of the altar sinks "
"down and is covered by an errie silverish colored fog.\n");
    set_weight(100000);
    set_value(70);
    z = 0;
    set_possible_to_close(1);
    set_max_internal_encumbrance(500);
    toggle_closed();
    set_lock("locked");
    set_key("ababababab");
}

