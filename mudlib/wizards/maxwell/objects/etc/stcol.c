//    Maxwell's Underground Mudlib 
//          Steel Column of Axe of Dulith
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("steel column");
    set_id( ({ "steel column","column","the steel column" }) );
   set_short("a steel column" );
    set_long("A large steel column. The top of pillar looks like "
"it was designed to hold a long straight shaft of some type");
    set_weight(100000);
    set_value(70);
}
int movel(object dest) { 
    if( living( this_player() ) ){
       if( (this_player()->query_name()) == "maxwell"){
         write("Move allowed cause your Max");
         ::move(dest);
         return;
       }
       else {
        write("The column is attached to the temple floor.");
        return 1;
       }
    }
    else {
      ::move(dest);
    }
}

int desc(string fun){
    set_long("The steel column is shaking softly. A long steel "
    "shaft has been locked in place on the top of the column.");
     return 1;
}
