#include <std.h>

inherit ROOM;

void create() {
  ::create();
    set_property("indoors", 1);
    set_property("light", 2);
    set("short", "The Blue Dragon Inn foyer");
    set("long",
	"You reach a second-story landing.  You see hallways leading "+
	"to the south, east, and west.  You see a staircase leading up and down.");
    add_exit("/d/damned/inn/foyer", "down");
    add_exit("/d/damned/inn/foyer3", "up");
    add_exit("/d/damned/inn/hall_20", "west");
    add_exit("/d/damned/inn/hall_21", "south");
    add_exit("/d/damned/inn/hall_22", "east");
    return;
}

