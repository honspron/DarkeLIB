//    Maxwell's Underground Mudlib
//       Exit Trap Object

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;
object here;

create() {
    ::create();
   set_id(({"rut","ruts"}));
   set_name("rut");
   set_short("test");
   set("long", "These ruts are very deep in the ground");
   set_weight(2);
   set_value(0);
}
int get() { 
    return 0;
}
int query_trap_level(){
    return 6;
}
int disarm_trap(){
    here = environment(this_object());
    tell_room(here,"Trap disarmed.");
    return 1;
}
int spring_trap(){
    here = environment(this_object());
    tell_room(here,"The trap springs.");
    return 1;
} 
