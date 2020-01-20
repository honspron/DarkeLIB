//    Maxwell's Underground Mudlib 
//          Mine Key for Alcove Door
#include "/adm/include/std.h"
inherit OBJECT;

void create() {
  ::create();
    set_name("mine key");
    set_id( ({ "mine key","key","iron key","iron mine key" }) );
    set_short("a small iron mine key" );
    set_long("The key is made from a solid piece of iron. Engraved into "
"the shaft of the key are assorted symbols of the Dwarven culture.");
    set_weight(10);
    set_value(0);
}

