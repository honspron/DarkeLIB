//Maxwell's Underground mudlib
//Thief Guild

#include <std.h>
#include <under.h>
inherit ROOM;

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a small stone passage.\n");
  set("long", "Test Room 13");
  set_exits( ({ UNTHIEF+"thief12" }),
             ({ "northwest" }) );
  set_items( ([
    "walls" : "The cold stone walls are covered with cracks.",
    "passage" : "The passage leads off into the darkness below.",
    "torches" : "The small oil torches are bolted to the walls.",
    "staircase" : "The thick stone steps are slightly damp.",
  ]) );
  set_smell("default", "The heavy dust clouds the air.");
  set_listen("default","You can hear nothing but the beat of your heart.");
}


