//      From Maxwell's Underground mudlib
//          Generic Room for Dwarf Mining Zone

#include "/adm/include/std.h"
#include "under.h"

inherit ROOM;

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are standing in a mining tunnel.");
    set("long", 
       );
    set_exits( ({ "/wizards/maxwell/workroom", "/wizards/maxwell/underzone/dme" }),
      ({ "workroom", "entrance" })
    );
    set_items( ([
       "water" : "There must be an underground spring near here.",
       "straw" : "The moldy straw sticks to the stone floor.",
      ]) );
}
