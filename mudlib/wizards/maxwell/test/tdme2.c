//      From Maxwell's Underground mudlib
//          Entrance Room for Dwarf Mining Zone

#include "/adm/include/std.h"
//inherit ROOM;
inherit "/wizards/maxwell/trap3";
inherit "wizards/maxwell/vault";

int x,safe;
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short",
 "You are standing at the entrance to the Dwarf mine."
       );
    set("long", 
"You are standing in the entrance tunnel to the Under'Drin Mines. "
"The smooth tunnel walls look like they were carved out by dedicated "
"workers. There are thick support timbers evenly spaced along the "
"tunnel walls and across the ceiling.\nThe floor has deep ruts cut into "
"it. The loaded mining carts that pass through here must be very heavy."
       );
    set_exits( ({ "/wizards/maxwell/underzone/dm1", 
"/wizards/maxwell/underzone/dmc" }),
      ({ "north", "south" })
    );
   set_door("gate", "/wizards/maxwell/underzone/dmc", "south", 0);
   set_string("gate", "close", "You pull against the heavy gate "
      "until it slides shut with a loud clang.\n"); 
   set_string("gate", "open", "You hear the heavy gate groan as "
      "you push it open.\n"); 
    set_items( ([
       "timbers" : "The timbers must have been cut from huge trees in the forest.",
       "rut*" : "The ruts are several inches deep.",
      ]) );
       
//    set_smell("default", "It smells like a new immortal in here.");
//    set_listen("default", "You hear the sounds of code creation.");
  set_pre_exit_functions(({"north" }),
    ({"trap_check"}) );
    trap_active = "armed";
    trap_type = "Explosive";
    trapped_exit = "ruts";
    x = 0;
    safe_players = ({});
   set_door("gate", "/wizards/maxwell/underzone/dmc", "south", 0);
   set_string("gate", "close", "You pull against the heavy gate "
      "until it slides shut with a loud clang.\n"); 
   set_string("gate", "open", "You hear the heavy gate groan as "
      "you push it open.\n");  
}
void look_at_door() {
   if(query_open("gate")) write("The gate has been pushed open.");
   else write("The gate is tightly shut.");
}
int init() {
    ::init();

    if(this_player()->is_player() || this_player()->is_pet()) return 1;
    else {
     this_player()->force_me("north");
     return 1;
     }
  
}
int query_safe(){
    return sizeof(safe_players);
}
void reset() {
    ::reset();
    set_open("gate",0);
}

