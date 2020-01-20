#include "/adm/include/std.h"

inherit ROOM;

void create() {
	::create();
	set_property("indoors", 2);
	set_property("light", 3);
	set("short", "A mystical chamber of light.");
	set("long", "This is a strange room, light seems to get to every where in this room, even though there are objects that would usually create shadows.  In the middle of the room is a sword, maybe something that could help newbies out.");
	set_exits( ({"/wizards/blial/areas/room2.c"}), ({"up"}));
}
void reset() {
   ::reset();
  if(!present("cube")) {
   new("/wizards/blial/monsters/blob.c")->move(this_object());
  }
}


