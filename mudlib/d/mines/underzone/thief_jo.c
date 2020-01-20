//  Maxwell's UnderGround Mudlib
//  Thief Guild Joining Room

#include "under.h"
inherit "/wizards/maxwell/join_roo";

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
    "east. A small secret doorway leads back into the sewer tunnel and "
    "a side passage leads to the north between two columns.\n"
    "A small plaque is nailed to one of the columns.");
  set_exits( ({ GUILDR+"thief4",GUILDR+"train_ro",GUILDR+"t_treas",
                GUILDR+"thief_sh" }),
             ({ "doorway","west","east","north" }) );
  set_items( ([
    "plaque"   : "The small wooden plaque is nailed into the column. Maybe "
                 "you can read it.",
    "column"   : "The thick columns stretch up and support the ceiling.",
    "doorway"  : "The small doorways is hidden among the shadows.",
  ]) );
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
