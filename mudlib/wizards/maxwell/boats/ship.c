//Maxwell's Underground Mudlib
//Wooden Ship

#include "under.h"
inherit BOAT+"boat.c";

void create() {
  ::create();
    set_name("ship");
    set_id( ({ "ship","boat","wooden ship" }) );
    set_short("a huge wooden ship" );
    set("long", 
    "This large ship is made from huge wooden timbers. The sides "
    "are covered with tiny barnacles and dark water stains. It looks big "
    "enough to hold a lot of equipment and a large number of passengers.\n");
    set_weight(100000);
    set_property("no clean",1);
    set_property("boat",1);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(5000);
//Boat Code
    set_property("ship",1);
    armour = 3;
    anchor_raised = 1;
    exit_names = ({"cabin","crowsnest"});
    exit_paths = ({BOATR+"cabin",BOATR+"crow"});
    exit_returns = ({"deck","deck"});
    main_room = file_name(this_object());
}

