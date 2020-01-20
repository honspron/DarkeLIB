//    Maxwell's Underground Mudlib 
//          Gold Column of Axe of Dulith
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("gold column");
    set_id( ({ "gold column","column","the gold column" }) );
   set_short("a gold column" );
    set_long("It is a 4 foot column of solid gold that rises out "
"of the stone floor. The top of the column looks like it was designed "
"to hold a large smooth object.");
    set_weight(100);
    set_value(70);
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
int desc(string fun){
    set_long("The golden column is shaking softly. A large gold axe blade "
"has been placed on the top of the column.");
     return 1;
}
