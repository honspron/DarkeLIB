//      From Maxwell's Underground Mudlib
//             Mining Cart

inherit "/std/bag_logic";

void create() {
    set_id( ({"cart"}) );
    set_name("cart");
    set("short", "a large mining cart");
    set_weight(300);
    set("long", 
"A cart.\n");
    set_value(50);
    set_max_internal_encumbrance(800);
    call_out("exit",5,this_object());
}
int exit(string fun){
   write("This is a test.");
}
