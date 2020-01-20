//    Maxwell's Underground Mudlib 
//             Burlap Bag of Ore
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("burlap bag of ore");
    set_id( ({ "ore bag","bag of ore","ore","bag","burlap bag of ore" }) );
   set_short("a burlap bag of raw ore" );
    set_long("This ore was dug out of the mine walls by the dwarves. "
"The dark rocks are jagged and broken. You can see several different "
"types of gems sparkling inside the bag.");
    set_weight(1500);
    set_value(70);
}

