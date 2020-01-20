//    Maxwell's Underground Mudlib 
//              Dynamite Block

#include <std.h>
#define BOULDER "/wizards/maxwell/underzone/dm24"
inherit OBJECT;
 
void create() {
  ::create();
    set_name("dynamite");
    set_id( ({ "dynamite" }) );
    set_short("a block of serveral sticks of dynamite");
    set_long("The dynamite block is made of several sticks of dynamite. "
"they are wrapped together with some sort of cloth.");
    set_weight(100);
    set_value(70);
}
int get(){
    write("You should probably not move the dynamite from the crate. You "
"have no idea how stable it is.");
    return 0;
}

