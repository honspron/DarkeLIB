//Maxwell's Underground mudlib
//Thief Guild

#include "/adm/include/std.h"
#include "under.h"
inherit ROOM;

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "You are standing in a small stone room.\n"
    "There is a strange portal on the far wall.\n");
  set("long", "You are standing in a small stone chamber. The cracked "
      "stone walls wrap around to form a circle barrier, broken "
      "only by a large shimmering portal.\n");
  set_exits( ({ UNTHIEF+"t_treas" }),({ "south" }) );
  set_items( ([
    "walls" : "The cold stone walls are covered with cracks.",
    "passage" : "The passage leads off into to the south.",
  ]) );
  set_smell("default", "The heavy dust clouds the air.");
  set_listen("default","You can hear nothing but the beat of your heart.");
}
int init() {
    ::init();
    add_action("check_exit","look");     
}
int check_exit(string str){
object *inv;
int y;

  if(str == "portal" || str == "at portal"){
    write("The strange portal is showing the image of another room.");
    inv=filter_array(all_inventory(find_object_or_load(UNTHIEF+"thief_du")),
       "is_living",this_object());
    if(sizeof(inv) == 0)
      write("The dungeon is empty.");
    else {
      write("The dungeon is occupied by "+sizeof(inv)+" living beings.");
      y = 0;
      while(y < sizeof(inv)){
           write(inv[y]->query_cap_name());
           y = y + 1;
      }
    }
    return 1;
  }
}


