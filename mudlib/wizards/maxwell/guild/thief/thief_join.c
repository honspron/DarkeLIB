//  Maxwell's UnderGround Mudlib
//  Thief Guild Joining Room

#include "under.h"
inherit UNTHIEF+"join_room";

void create() {
  set_class_name("thief");
  ::create();
  set_property("light",1);
  set_property("indoors", 1);
  set("short", "The Thieves Guild Joining Room");
  set("long", 
    "You are standing in an old temple room. The crumbling walls are "
    "covered in dust and filled with cracks. Huge columns are evenly "
    "spaced along the edge of the circular room. Some of them have begun "
    "to split and look unstable.\n"
    "Two archs lead to out of the room, one to the west and another to the "
    "north. A side passage leads to the south, back to the sewers.\n"
    "There is a small plaque nailed to one of the columns above a "
    "couple of iron rings.\n");
  set_exits( ({ UNTHIEF+"thief4",UNTHIEF+"train_room",UNTHIEF+"thief5" }),
             ({ "doorway","west","north" }) );
  set_pre_exit_functions(({"north" }), ({"class_check"}) );
  set_items( ([
    "plaque"   : "The small wooden plaque is nailed into the column. Maybe "
                 "you can read it.",
    "column"   : "The thick columns stretch up and support the ceiling.",
    "doorway"  : "The small doorways is hidden among the shadows.",
    "ring" : "The ring is smooth to the touch.",
    "rings" : "The thick rings are worn down and very smooth.",
  ]) );
  set_search("wall","There is a small plate at the base of the wall. "
             "looks like you can lift it!");
//Guildmaster Settings
  set("guildmaster", "/d/damned/guilds/thief/thief_gm");  
  set_guild_obj("/d/damned/guilds/thief/thief_obj");
//Guild Properties
  set_property("base hp regen", 4);
  set_property("base mp regen", 4);
  set_property("hp advance", 28);
  set_property("mp advance", 8);
  set_property("guild mods", ([ "dexterity" :  10, "charisma" : 10 ]) );
//Misc Code
  new("d/damned/guilds/join_rooms/tcan")->move(this_object());
  set_related_guilds(({ "nightblade", "fighter" }));
  this_object()->reset();
  return;
}
int class_check(){
  if(this_player()->query_class() != "thief" && !wizardp(this_player()) ){
    write("A magical force stops you from going that way!");
    return 0;
  }
  else
   return 1;
}

