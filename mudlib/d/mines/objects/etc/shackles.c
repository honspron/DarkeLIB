//    Maxwell's Underground Mudlib
//           Dwarven Slave Shackles

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

create() {
    ::create();
   set_id(({"shackles","dwarven shackles"}));
   set_name("shackles");
   set_short("a set of Dwarven shackles");
   set("long", "This set of Dwarven shackles looks well used. You "
"can see deep rub marks in the loops that wrap around and restrain "
"the wrists.");
   set_weight(20);
   set_value(45);
}

