#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "East Gate Tower.");
	set("long", "Standing high above the eastern entrance to the walled city this solid tower allows the guards to view all who approach.");

	add_exit(ROOMS+"dirtpath5","down");
	add_exit(ROOMS+"tower2","west");

	set_listen("default", "The wind whistles by your ears at this height.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());

}
