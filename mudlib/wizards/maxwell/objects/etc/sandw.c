//         Maxwell's Underground Mud Library
//               Roast Beef Sandwich
 
#include "/adm/include/std.h"

inherit "/std/food";

 
void create() {
  ::create();
    set_name("sandwich");
    set_id( ({ "beef", "sandwich", "roast beef sandwich" }) );
    set_short("roast beef sandwich");
    set_long("A thick, juicy roast beef sandwich.");
    set_weight(10);
    set_strength(35);
    set_float_value(4.0);
    return;
}
