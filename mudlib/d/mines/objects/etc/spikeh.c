//    Maxwell's Underground Mudlib 
//         Spiked Skull
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("skull");
    set_id( ({ "skull","spiked skull","spike" }) );
   set_short("a spiked skull" );
    set_long("The rotten skull is firmly jammed onto the spike. The thought "
"of your skull being there chills you to your bones.\n");
    set_weight(30);
    set_value(70);
}
void get() { 
    write("It is securly embedded in the floor.");
//    if(query("get message")) write(query("get message"));
    return;
}

