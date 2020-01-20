//    Maxwell's Underground Mudlib
//           Dwarven Vase

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

create() {
    ::create();
   set_id(({"vase","dwarven vase"}));
   set_name("vase");
   set_short("a Dwarven vase");
   set("long", "This pottery and metal vase is covered with engraved "
"symbols and figures reflecting the long history of the Dwarven race. "
"You see an image representing the Dwarven Lost City of Mantar");
   set_weight(100);
   set_value(150);
}

