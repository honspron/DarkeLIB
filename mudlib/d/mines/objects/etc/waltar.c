//    Maxwell's Underground Mudlib 
//          Wooden Altar of Axe of Dulith
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("altar");
    set_id( ({ "altar" }) );
   set_short("a wooden altar" );
    set_long("The altar is made of solid oak that must have been "
"cut in the dwarven forest. The center of the altar has been raised, "
"but whatever was on the platform has been removed.");
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
