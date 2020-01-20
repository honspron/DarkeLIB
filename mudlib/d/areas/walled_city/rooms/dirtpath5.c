#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 0);

	set("short", "East Gate.");
	set("long", "A solid rock tower looms overhead. There is a heavy wooden gate on the narrow entrance beneath the tower which can be quickly closed. High above you a guard peers out of slit window. From the west you hear voices and laughter. To the east a well maintained dirt path leads away from the city.");

	add_exit(ROOMS+"dirtpath4","east");
	add_exit(ROOMS+"grounds1","west");
	add_exit(ROOMS+"tower1","up");

     set_items(([
          ({ "dirt", "path" }) :
          "A well maintained dirt path leads off to the east.",
          ({ "gate" }) :
          "The gate is wooden, but clad with iron and appears to be quite sturdy.",
          ({ "tower" }) :
          "The tower stands bravely against the sky, protecting the eastern entrance to the walled city."
     ]));
     set_smell("default", "It smells like someone cut the cheeze here.");
}	
void reset() {
	::reset();
if(!present("guard"))
{
new(MON+"guard.c")->move(this_object());
new(MON+"guard.c")->move(this_object());
new(MON+"moving_guard.c")->move(this_object());
}
}
