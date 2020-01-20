//    Maxwell's Underground Mudlib 
//          Wooden Column of Axe of Dulith
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("wooden column");
    set_id( ({ "wooden column" }) );
   set_short("a wooden column" );
    set_long("A large wooden column. The top of pillar looks like "
"it was designed to hold a rod of some type");
    set_weight(100);
    set_value(70);
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}

int desc(string fun){
    set_long("The wooden column is shaking softly. A long wooden "
"shaft has been locked in place on the top of the column.");
     return 1;
}
