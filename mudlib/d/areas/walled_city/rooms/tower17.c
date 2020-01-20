#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard tower.");
	set("long", "The solidly built rock tower protects the city.");

	add_exit(ROOMS+"tower16","north");
	add_exit(ROOMS+"tower18","east");
	add_exit(ROOMS+"grounds25","down");

	set_listen("default", "The constant wind whistles loudly.");
}
void reset() {
	::reset();
if(!present("guard"))
new(MON+"guard.c")->move(this_object());
}
