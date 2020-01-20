//	An example skill training room for the fighter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95
 
inherit "/std/guilds/skill_room";
 
void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "thief_board"}) );
  ob->set_board_id("thief_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/thief/train_room");
  ob->set("short","Thief Board");
  ob->set("long","A bulletin board on which are posted several notes.\n");
  set("short", "The Thief Guild Training Room");
  set("long", 
"This is the room where thieves come to hone their mischievous and "
"deadly skills.  Several dark figures here wield deadly-looking swords "
"and spar with one another.  A few stand in one corner and are trying "
"to pick open the lock on a large chest.  Two especially strong thieves "
"argue about the best way to execute a back stab."
"\nTo the west is the treasury.  The fee to enter is 5 silver per level.\n");
  //  "\n" important here, too.
 
  set_items( ([
                "thief" : "one of the thieves glances at you and grins.",
                "thieves" : "They all look quite skilled.",
                "chest": "The large chest is stolen, most likely.",
                ]));
  set_property("light",1);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/thief_join");
 
  set_exits( ([
                "east" : "/d/damned/guilds/join_rooms/thief_join",
                "south" : "/d/damned/guilds/thief/thief_shop",
                "west" : "/d/damned/guilds/thief/t_treas",
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
  add_skill("attack",1);
  add_skill("perception", 1);
  add_skill("dance of daggers", 5);
  add_skill("parry", 1);
  add_skill("dodge", 1);
  add_skill("poison lore", 10);
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
  if(!present("guard")) 
    new("/d/damned/guilds/thief/t_guard")->move(this_object());
  return;
}
