#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
     ::create();
     set_property("light", 1);
     set_property("indoors", 0);

	set("short", "Guard tower.");
	set("long", "This solidy build guard tower provides protection for the citizens of the walled city.");

	add_exit(ROOMS+"tower19","north");
	add_exit(ROOMS+"tower17","west");
	add_exit(ROOMS+"grounds24","down");

	set_listen("default", "The wind whistles loadly.");
}
