//      From Maxwell's Underground mudlib
//          Entrance Room for Dwarf Mining Zone


#define UNDER "/wizards/maxwell/underzone/"

inherit "/wizards/maxwell/trap3";
//inherit "/std/room";

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
    set_exits( ({ UNDER+"dm1",UNDER+"dmc" }), ({ "north", "south" }) );

    set_pre_exit_functions(({"north" }), ({"trap_check"}) );

//Trap Code Variable
    trap_active = "armed";
    trap_type = "Explosive";
    trapped_exit = "ruts";
    safe_players = ({});
    x = 0;
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
//void reset() {
//    ::reset();
//    set_open("gate",0);
//}

