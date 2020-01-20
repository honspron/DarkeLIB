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
  ob->set_id( ({"board", "fighter_board"}) );
  ob->set_board_id("fighter_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/fighter/train_room");
  ob->set("short","Fighter Board");
  ob->set("long","A board for players to post notes.\n");
  set("short", "The Fighters' Training Room");
  set("long", "This is the room where fighters come to hone their "+
        "great skills.\nTo the east is the treasury.  A donation off "+
"5 silver per level is required to enter, but you may store items there.");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/fighter_join");

  set_exits( ([ "south" : "/d/damned/guilds/join_rooms/fighter_join",
                "east" : "/d/damned/guilds/fighter/f_treas" ]));
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("blade", 1);
  add_skill("combat awareness", 9);
  add_skill("consider", 1);
  add_skill("trade lore", 1, 1);
  add_skill("whirlwind attack", 5);
  add_skill("reverse stroke", 10);
  add_skill("offhand training", 4);
  add_skill("dual attack", 10);
  add_skill("resist stun", 10);
  add_skill("two handed blade", 1);
  add_skill("attack", 1);
  add_skill("melee", 1);
  add_skill("parry", 1);
  add_skill("focused attack",16);
  add_skill("sweep", 7);
  add_skill("block", 1);
  add_skill("prospecting", 1, 1);
  add_skill("blunt", 1);
  add_skill("two handed staff", 1);
  add_skill("two handed blunt", 1);
  add_skill("flail", 1);
  add_skill("two handed flail", 1);
  add_skill("axe", 1);
  add_skill("two handed polearm", 1);
  add_skill("knife", 1);
  add_skill("thrown", 1);
  add_skill("perception", 1);
  add_skill("swimming", 1);
  add_skill("body block", 1);
  add_skill("compare", 3);
  add_skill("shield bash", 3);
  add_skill("bash lock", 11, 1);
  add_skill("dodge", 3);
  add_skill("kick", 4);
  add_skill("reverse punch", 6);
  add_skill("martial arts", 1);
  return;
}

void reset() {
  if(!present("guard", this_object()))
    new("/d/damned/guilds/fighter/t_guard")->move(this_object());
  return;
}

  
