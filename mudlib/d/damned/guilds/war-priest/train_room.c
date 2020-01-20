//	An example skill training room for the paladin's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "war-priest_board"}) );
  ob->set_board_id("war-priest_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/war-priest/train_room");
  ob->set("short","War-Priest Board");
  ob->set("long","A board for players to post notes.\n");
  set("short", "The war-priests' Training Room");
  set("long", "This is the room where war-priests come to hone their "+
	"great skills.\nTo the west is the treasury.  The fee for entry is "
        "5 silver per level.\n");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");

  add_exit("/d/damned/guilds/join_rooms/war-priest_join", "south");
 add_exit("/d/damned/guilds/war-priest/wp_treas", "west");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("worship of k'thach", 1);
  add_skill("prayer", 1);
  add_skill("parry", 3, 1);
   add_skill("trade lore", 1, 1);
  add_skill("block", 1, 1);
  add_skill("body block", 3, 1);
  add_skill("dodge", 5, 1);
  add_skill("attack", 1);
  add_skill("melee", 1, 1);
  add_skill("body alteration", 2);
   add_skill("swimming",1);
  add_skill("blunt", 1);
  add_skill("blade", 1, 1);
  add_skill("two handed blunt", 1);
  add_skill("flail", 1, 1);
  add_skill("prospecting", 1, 1);
  add_skill("two handed flail", 1, 1);
  add_skill("two handed blade", 5, 1);
  add_skill("compare", 3, 1);
  add_skill("perception", 1, 1);
  add_skill("consider", 1);
  add_skill("offhand training", 10, 1);
  add_skill("dual attack", 17, 1);
  add_skill("concentrate",3);
  return;
}

void reset() {
  ::reset();
  if(!present("guard")) new("/d/damned/guilds/war-priest/t_guard")->
      move(this_object());
  return;
}

