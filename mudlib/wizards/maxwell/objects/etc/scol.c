//    Maxwell's Underground Mudlib 
//          Silver Column of Axe of Dulith
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("silver column");
    set_id( ({ "silver column","column","the silver column" }) );
   set_short("a silver column" );
    set_long("It is a 4 foot column of solid silver that rises "
"out of the stone floor. The top of the column looks like it was "
"designed to hold a large smooth object.");
    set_weight(100);
    set_value(70);
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
int desc(string fun){
    set_long("The silver column is shaking softly. A large silver "
"axe blade has been placed on the top of the column.");
     return 1;
}
