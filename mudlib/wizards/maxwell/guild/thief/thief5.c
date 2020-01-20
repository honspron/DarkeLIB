//Maxwell's Underground mudlib
//Thief Guild

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a small stone passage.\n");
  set("long", "You are standing in a small stone passage. The cracked "
      "stone walls stretch before you in both directions, broken "
      "only by the evenly spaced torches.");
  set_exits( ({ UNTHIEF+"thief_shop",UNTHIEF+"thief_join" }),
             ({ "north","south" }) );
  set_items( ([
    "walls" : "The cold stone walls are covered with cracks.",
    "passage" : "The passage leads off into the darkness to the north.",
    "torches" : "The small oil torches are bolted to the walls.",
  ]) );
  set_smell("default", "The heavy dust clouds the air.");
  set_listen("default","You can hear nothing but the beat of your heart.");
}


