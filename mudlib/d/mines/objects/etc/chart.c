//    Maxwell's Underground Mudlib
//           Dwarven Dust Tube Chart

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

create() {
    ::create();
   set_id(({"chart","dust chart"}));
   set_name("chart");
   set_short("a wooden chart");
   set("long", "This wooden chart has inventory lists on it. You notice "
   "that the mine has a large quantity of Zikert Dust Tubes. It must be "
   "the primary explosive for the mine.");
   set_weight(5);
   set_value(10);
}
int get() { 
    write("You try to lift the chart off the wall, but it is bolted there.");
    return 0;
}
