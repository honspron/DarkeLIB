//       Maxwell's Underground Mudlib 
//             Corpse Dester
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("dester");
    set_id( ({ "dester" }) );
   set_short("a corpse dester" );
   set_long("This removes mob's corpses.");
    set_weight(1);
    set_value(0);
}
int nuke_environment(){
   call_out("nuke",2,this_object());
   return 1;
}
int nuke(){
   environment(this_object())->remove();
   remove();
   return 1;
}
