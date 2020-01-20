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
  set("long", "You are standing in a small stone passage. The cracked "
      "stone walls stretch before you in both directions, broken "
      "only by the evenly spaced torches.\n"
      "There is a large stone staircase here, lowering into the "
      "depths of the temple.");
  set_exits( ({ STDTHIEF+"thief_join",UNTHIEF+"t_treas" }),
             ({ "doorway","staircase" }) );
  set_items( ([
    "walls" : "The cold stone walls are covered with cracks.",
    "passage" : "The passage leads off into the darkness below.",
    "torches" : "The small oil torches are bolted to the walls.",
    "staircase" : "The thick stone steps are slightly damp.",
  ]) );
  set_smell("default", "The heavy dust clouds the air.");
  set_listen("default","You can hear nothing but the beat of your heart.");
}


