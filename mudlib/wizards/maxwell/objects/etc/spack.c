//      From Maxwell's Underground Mudlib
//               Saddle Bag

inherit "/std/bag_logic";

void create() {
    set_id( ({"saddle bag","bag"}) );
    set_name("saddle bag");
    set("short", "a large leather saddle bag");
    set_weight(100);
    set("long", "This saddle bag is designed to be carried by a large "
"pack animal. It has a large pouch on the side for holding things.\n");
    set_possible_to_close(1);
    set_value(50);
    set_max_internal_encumbrance(800);
}

