//       Maxwell's Underground Mudlib 
//              Lead Chain
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("chain");
    set_id( ({ "chain","collar" }) );
   set_short("a long steel link chain" );
   set_long("This chain is used to control the wolves.");
    set_weight(100);
    set_value(70);
}
int dis(string fun){
   remove();
}

