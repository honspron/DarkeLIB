//	An example skill training room for the enchanter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
ob = new("std/bboard");
ob->set_name("board");
ob->set_id( ({"board", "enchanter_board"}) );
ob->set_board_id("enchanter_board");
ob->set_max_posts(25);
ob->set_location("d/damned/guilds/enchanter/train_room");
ob->set("short","Enchanter Board");
ob->set("long", "A board for players to post notes.\n");
ob->set_edit_ok( ({"/d/damned/guilds/join_rooms/enchanter_join"->query_master() }) );
  set("short", "The Enchanters' Training Room");
  set("long", "This is the room where enchanters come to hone their "+
	"skills of crafting and enchanting.  It is more of a laboratory "
        "than a training room.  There are various experiments and machines "
        "scattered throughout the room.\n");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/enchanter_join");

  add_exit("/d/damned/guilds/join_rooms/enchanter_join", "south");
  add_exit("/d/damned/guilds/enchanter/e_treas", "east");
  add_exit("/d/damned/guilds/enchanter/enchanter_spell_room", "west");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("trade lore", 1);
  add_skill("energy manipulation", 1);
  add_skill("enchantment", 1);
  add_skill("detect magic", 5);
  add_skill("spell sense", 12);
  add_skill("perception", 1);
  add_skill("attack", 1);
  add_skill("melee", 1);
  add_skill("knife", 1);
  add_skill("consider", 1);
  add_skill("thrown", 1);
  add_skill("concentrate", 5);
  add_skill("two handed staff", 1);
  add_skill("perception", 1, 1);
  add_skill("swimming", 1);
  add_skill("prospecting", 1);
  add_skill("dodge", 4);
  add_skill("blade", 3, 1);
  add_skill("focus casting", 5, 1);
  add_skill("fast casting", 12, 1);
  add_skill("blunt", 3, 1);
  return;
}

void reset() {
  ::reset();
  if (!present("guard"))
      new("/d/damned/guilds/enchanter/t_guard")->move(this_object());
  return;
}





