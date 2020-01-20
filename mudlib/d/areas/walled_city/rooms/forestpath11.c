#include <std.h>
#include "../walled_city.h"
inherit ROOM;

	void create() {
	::create();

	set_property("light", 0);
	set_property("outdoors", 0);

 	set("short", "Forest path.");
        set("long", "You stand in a heavily forested area. The ancient hardwood trees loom over you. Thick branches reach in all directions. The canopy of heavy leaves blocks out all natural light.");

       add_exit(ROOMS+"forestpath12","north");
       add_exit(ROOMS+"forestpath10","south");

       set_items(([
       ({ "leaf", "leaves" }) :
       "The leaves here grow large and thick, and block out all natural light from the sky.",
       ({ "tree", "trees","oak", "oaks", "hardwoods" }) :
       "The old trees dominate the landscape, branches intertwined high above the nearly barren forest floor."]));

       set_listen("default", "Something chrashes through the underbrush.");

}
