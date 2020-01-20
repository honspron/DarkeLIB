// Entry to Muerta Canyon
// Created by Zortek
// 031596

#include <std.h>
#include "/wizards/zortek/canyon/canyon.h"

inherit ROOM;

void init() {
    ::init();
}

void reset() {
  ::reset();
}

void create() {
    ::create();
    set_property("light", -4);
    set_property("indoors", 0);
    set_property("night light",-4);
    set("short", "The Well of Souls");
    set("long",@TEXT
You are in a cylindrical shaft reaching deep into the earth.
There seems to be a moderate wind blowing downward, but
fortunately the rungs seem steady and secure.
TEXT
);
    add_exit(ROOMS+"well1", "up");
    add_exit(ROOMS+"well3", "down");
    set_items(([
    ({ "rung", "rungs", "iron rung", "iron rungs" }): @RUNG
These loops of metal have been set into the wall of the well at
comfortable intervals that makes descent relatively easy in the
highly close quarters.  Despite the moist air, the rungs show no
evidence of corrosion.
RUNG
,
    ]));
    set_smell("default", "Fresh air seems to blow from above.");
    set_listen("default", "The wind makes a faint moaning sound.");
   reset();
}
