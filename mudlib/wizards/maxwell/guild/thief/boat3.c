//Maxwell's Underground Mudlib
//Wooden Ship

#include "under.h"
inherit "/wizards/maxwell/guild/thief/boat2.c";

void create() {
  ::create();
    set_name("ship");
    set_id( ({ "ship","boat","wooden ship" }) );
    set_short("a huge wooden ship" );
    set("long", 
    "This is a large ship is made from huge wooden timbers. The sides "
    "are covered with tiny barnacles and deep water stains. It looks big "
    "enough to hold a lot of equipment and a large number of passengers.\n");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(0);
    set_max_internal_encumbrance(5000);
//Boat Code
    anchor_raised = 1;
    exit_names = ({"cabin","crowsnest"});
    exit_paths = ({UNDER+"cabin",UNDER+"crow"});
    exit_returns = ({"deck","deck"});
    main_room = file_name(this_object());
}
