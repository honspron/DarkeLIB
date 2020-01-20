//Maxwell's UnderGround Mudlib
 
#include "under.h"
inherit UNTHIEF+"skill_ro";
 
void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "thief_board"}) );
  ob->set_board_id("thief_board");
  ob->set_max_posts(25);
  ob->set_location(UNTHIEF+"train_room");
  ob->set("short","Thief Board");
  ob->set("long","A bulletin board on which are posted several notes.\n");
  set("short", "The Thief Guild Training Room");
  set("long", 
"You are standing in a dusty side chamber. The cracked ceiling slopes "
"upward and ends at the base of a large suspended candle chandelier.\n"
"Bolted on to the walls are large wooden slabs and various tools "
"of training. The floor of the chamber is soiled with dirty footprints "
"and stains of blood and sweat.\n"); 
  set_items( ([
    "stains" : "The grimy stains are covering the the cracked stones.",
    "chandelier" : "The old chandelier is covered with spider webs and dust.",
    "slabs": "The large wooden slabs are covered with grooves from "
             "throwing knives.",
                ]));
  set_property("light",1);
  set_property("indoors", 1);   
  set_join_room(GUILDR+"thief_jo"); 
  set_exits( ([
     "east" : UNTHIEF+"thief_join",
   ]) );
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	spell 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.
  add_skill("knife", 1);
  add_skill("consider", 1);
  add_skill("detect trap", 6);
  add_skill("disarm trap", 10);
  add_skill("thrown", 1);
  add_skill("disguise", 8);
  add_skill("blade", 1);
  add_skill("swimming", 1);
  add_skill("poison lore", 10);
  add_skill("attack",1);
  add_skill("perception", 1);
  add_skill("dance of daggers", 5);
  add_skill("parry", 1);
  add_skill("dodge", 1);
  add_skill("pick pocket", 1);
  add_skill("dual attack", 19);
  add_skill("prospecting", 1, 1);
  add_skill("steal", 4);
  add_skill("hide in shadows", 3);
  add_skill("stealth", 4);
  add_skill("invisibility art", 12);
  add_skill("shadow", 15);
  add_skill("stalk", 10);
  add_skill("pick locks", 6);
  add_skill("lock smithing", 19);
  add_skill("back stab", 8);
  add_skill("offhand training", 14, 1);
  add_skill("compare", 3);
  add_skill("trade lore",1);
  add_skill("martial arts", 18, 1);
  return;
}
 
void reset() {
  ::reset();
  if(!present("trainer")) 
    new(UNTHIEF+"trainer")->move(this_object());
  return;
}
