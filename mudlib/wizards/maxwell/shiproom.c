// -=*Inside the patagonia*=- 7-13-96
// - Written by Gabriel

#include "/adm/include/std.h"
#include "/adm/include/ansi.h"
#include "/adm/include/gab.h"

//MISSING this wizards code
#define PORT_A "/wizards/gabriel/dhyralos/ship/patagoniadock.c"
#define PORT_B "/wizards/gabriel/dhyralos/ship/braedock.c"

inherit "std/room";

       
void to_port_b(){
   tell_room(this_object(), "Arrived to Dhyralos.. .\n");
   call_other(PORT_B, "loadship");
   add_exit(PORT_B,"ashore");
   delayed_call("wait_in_port_b",10);
   return;
}
void wait_in_port_b(){
   remove_exit("ashore");
   call_other(PORT_B, "removeship");
   tell_room(this_object(), "Shove off! heading towards Kuril's\n");
   delayed_call("to_port_a", 20);
   return;
}        
void to_port_a(){
   tell_room(this_object(),"Arrived to Kuril's\n");
   call_other(PORT_A, "loadship");
   add_exit(PORT_A,"ashore");
   delayed_call("wait_in_port_a",10);
   return;
}
void wait_in_port_a(){
   remove_exit("ashore");
   tell_room(this_object(),"Shove off! heading towards Dhyralos\n");
   call_other(PORT_A, "removeship");
   delayed_call("to_port_b",20);
   return;
}


void create(){
        int to_port_b, to_port_a, wait_in_port_a, wait_in_port_b;
	::create();
	set_property("indoors", 1);
        set_property("light", 3);
        set("short", "Inside The Patagonia");
        set("long",
"   You are in the Drago Majestic Patagonia. She is a nice roomy ship.\n"
"It is set to sail to the great city of Brae, in the land of Dhyralos.\n"
"The hull is huge and sturdy, built with a heavy dark wood.\n"
"   The mast is taller than many of the trees you've seen. On top you\n"
"see a sailor that is on the look out for land. The whole ship is in\n"
"the shape of a huge dragon.\n");
        
set_smell("default","You smell the salty ocean air.");
set_listen("default","The hear the waves against the sides of the ship.");
add_exit(PORT_A,"ashore");
add_exit(SHIP+"shipmast","mast");
delayed_call("wait_in_port_a",10);
}
