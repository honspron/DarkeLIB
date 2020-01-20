//Maxwell's Underground mudlib
//Thief Guild

#include <std.h>
#include "under.h"
inherit ROOM;

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a slimy stone passage.\n");
  set("long", "You are standing in a slimy stone passage. Cold water "
      "drips down from the ceiling, combining with the dusty spider webs. "
      "The center of the passage is sumerged with a dark smelly liquid.\n"
      "There is a juntion here. A passage leads to the northwest and "
      "another tunnel stretches to the west.\n");
  set_exits( ({ GUILDR+"thief2",GUILDR+"thief4" }),
             ({ "northwest","west" }) );
  set_items( ([
    "walls" : "The cold stone walls are wet with running water.",
    "passage" : "The passage leads off into the darkness to the east.",
    "liquid" : "The nasty smelling liquid is filling most of the passage.",
  ]) );
  set_smell("default", "The smell of the foul liquid fills your nose.");
  set_listen("default","You can hear the loud sound of falling water to "
             "the west.");
}


