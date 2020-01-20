//Maxwell's Underground mudlib
//Thief Guild

#include <std.h>
#include "under.h"
inherit ROOM;

int x;
void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a slimy stone passage. The passage "
      "end here. There is a large grate in the flow into which the foul "
      "smelling liquid is draining.\n");
  set("long", "You are standing in a slimy stone passage. The cold stone "
      "walls stretches back to the east and stops at another wall to the "
      "west. The center of the passage is sumerged with a dark smelly "
      "liquid.\n"
      "The liquid is pouring into a huge grate in the floor.\n");
  set_exits( ({ GUILDR+"thief3" }),({ "east" }) );
  set_items( ([
    "walls" : "The cold stone walls are wet with running water.",
    "passage" : "The passage leads off into the darkness to the east.",
    "liquid" : "The nasty smelling liquid is filling most of the passage.",
    "grate" : "The large steel grate is rusty and covered with strange "
              "lichens and molds.",
  ]) );
  set_smell("default", "The smell of the foul liquid fills your nose.");
  set_listen("default","The sound of the draining liquid fills the "
             "passage.");
  set_search("grate","You find a small pullable steel lever hidden in the "
             "grate!");
  x = 0;
}
init(){
   ::init();
   add_action("pull_lever","pull");
}
int pull_lever(string str){
  if(!str){
    write("Pull what?");
    return 1;
  }
  if(str == "lever"){
    if(x == 0){
      write("You pull the small lever and a secret door slides opens in "
          "the wall!");
      add_exit(GUILDR+"thief_jo","doorway");
      x = 1;
    }
    else {
      write("You pull the lever and the secret door slides shut!");
      remove_exit("doorway");
      x = 0;
    }
    say(this_player()->query_cap_name()+" pulls on something in the "
       "grate.");
    return 1;
   }
}
