//    Maxwell's Underground Mudlib 
//              Gem bag
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("small bag of gems");
    set_id( ({ "gem bag","bag of gems","gems","bag"}) );
   set_short("a small bag of gems");
   set_long("A small bag of assorted gems. Some of the gems look "
   "fairly valuable." );
    set_weight(100);
    set_value(150);
}

