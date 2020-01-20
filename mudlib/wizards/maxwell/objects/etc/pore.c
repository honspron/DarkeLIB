//    Maxwell's Underground Mudlib 
//          Pile of Ore
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("pile of raw ore");
    set_id( ({ "ore pile","pile of ore","ore","pile"}) );
   set_short("a pile of raw ore" );
    set_long("This ore was dug out of the mine walls by the dwarves. "
"The dark rocks are jagged and broken. You can see several different "
"types of gems sparkling among them.");
    set_weight(1500);
    set_value(70);
}

