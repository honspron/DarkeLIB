#include <std.h>

inherit ROOM;

void create() {
  ::create();
    set_property("indoors", 1);
    set_property("light", 2);
    set("short", "The Blue Dragon Inn foyer");
    set("long",
	"You reach a third-story landing.  You see hallways leading "+
	"to the south, east, and west.  You see a staircase leading up and down.");
    add_exit("/d/damned/inn/foyer2", "down");
    add_exit("/d/damned/inn/foyer4", "up");
    add_exit("/d/damned/inn/hall_30", "west");
    add_exit("/d/damned/inn/hall_31", "south");
    add_exit("/d/damned/inn/hall_32", "east");
    return;
}

