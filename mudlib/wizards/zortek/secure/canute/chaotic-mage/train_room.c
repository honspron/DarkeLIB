//	An example skill training room for the paladin's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  set("short", "The Chaotic Lords' Training Room");
  set("long", "This is the room where Chaotic Lords come to hone their "+
	"great skills.\nTo the west is the treasury.  The fee for entry is "
       "5 gold per level.\n");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "chaotic-lord_board"}) );
  ob->set_board_id("chaotic-lord_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/chaotic-lord/chaotic-lord_train_room");
  ob->set("short","chaotic-lord board");
  ob->set("long","A board for players to post notes.\n");
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/chaotic-lord_join");

  add_exit("/d/damned/guilds/join_rooms/chaotic-lord_join", "east");
  add_exit("/d/damned/guilds/chaotic-lord/chaotic-lord_treas", "west");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("consider", 1);
  add_skill("perception", 1);
   add_skill("trade lore", 1, 1);
  add_skill("melee", 1);
  add_skill("attack", 1);
  add_skill("parry", 1);
  add_skill("swimming", 1);
   add_skill("prospecting", 1, 1);
  add_skill("blade", 1);
  add_skill("two handed blade", 1);
  add_skill("axe", 1);

  add_skill("two handed polearm", 2);
  add_skill("blunt", 2);
   add_skill("control demon", 2);
  add_skill("block", 2);
  add_skill("chaos magic", 2);

  add_skill("flail", 3);
  add_skill("two handed flail", 3);
  add_skill("two handed blunt", 3);
  add_skill("body block", 3);

  add_skill("thrown", 4);
  add_skill("compare", 4);
  add_skill("dodge", 4);
  add_skill("concentrate",3);

add_skill("offhand training", 9);

  add_skill("chaos lore",17);
   add_skill("reverse stroke",17,1);
  add_skill("dual attack", 12);

  
  return;
}

void reset() {
  ::reset();
  if(!present("guard")) new("/d/damned/guilds/chaotic-lord/t_guard")->
	move(this_object());
  return;
}
