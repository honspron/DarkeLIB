//    Maxwell's Underground Mudlib 
//          Steel Shaft of Axe of Montar
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("shaft");
    set_id( ({ "shaft","steel shaft" }) );
   set_short("a long steel shaft" );
    set_long("This thick shaft is made from high quality Dwarven Steel. "
    "The 4 foot shaft is engraved with symbols and ancient script. "
    "It has two long notches along the top end, and the base of the shaft "
    "is wrapped in leather.\n");
    set_weight(150);
    set_value(200);
}

