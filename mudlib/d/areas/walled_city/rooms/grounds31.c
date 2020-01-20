#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Captain's Quarters.");
        set("long", "This stark room is the home of the Captain of the Walled City Guards. To the east is the headquarters for all military operations. A narrow stairwell is here which may lead up into the tower.");

	add_exit(ROOMS+"tower14","up");
	add_exit(ROOMS+"grounds30","east");

	set_items(([
          ({ "stairwell", "stairs" }) :
                  "A dark, narrow passageway leading up several flights to what one would assume is the tower.",
          ({ "room", "walls", "floor" }) :
		  "A bare room with a small bed, neatly made and two wooden chairs."
	]));
	set_smell("default", "The air smells of stale tobacco smoke.");
	set_listen("default", "You hear footsteps from above.");

}
void reset() {
	::reset();
if(!present("guard"))
  {
        new(MON+"guard.c")->move(this_object());
  }
}
