//Maxwell's Underground mudlib
//Thief Guild

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a slimy stone passage somewhere "
      "beneath the city of Akkad.\n");
  set("long", "You are standing in a slimy stone passage somewhere "
      "beneath the city of Akkad. The cold stone walls stretch in front "
      "of you, leading to the southeast and the west.\nThere is a "
      "gushing stream of dark liquid pouring out of a pipe in the wall.");
  set_exits( ({ GUILDR+"thief1",GUILDR+"thief3" }),({ "west","southeast" }));
  set_items( ([
    "pipe" : "The steel pipe was pushed right through the wall. You "
             "can see where the stone was cracked and split.",
    "passage" : "The passage leads off into the darkness to the southeast "
             "and the west.",
    "liquid" : "The nasty smelling liquid is filling most of the passage.",
    "stream" : "The nasty smelling liquid is filling most of the passage.",
  ]) );
  set_smell("default", "The smell of the foul liquid fills your nose.");
  set_listen("default","The only sound you can here is the beat of your "
    "heart and the oozing of the liquid.");
  set_search("pipe","You find nothing of interest in the steel pipe.");
}


