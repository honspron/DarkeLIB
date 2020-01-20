inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
 ob->set_id( ({"board", "ranger_board"}) );
  ob->set_board_id("ranger_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/ranger/rg_skills");
  ob->set("short","Ranger Board");
  ob->set("long","A board for players to post notes.\n");
  set("short", "The Ranger's' Training Room");
  set("long", "This room has a few places where ranger's can pratice there
skills. There are a few books on a small book case in the far corner. The
books tell about skills that ranger's could learn. This is the room where
ranger's learn their skills and can practice some of them as well.\n");

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
set_join_room("/d/damned/guilds/join_rooms/ranger_join");

  add_exit("rg_treas", "east");
  add_exit("rg_forge", "southeast");
  add_exit("rg_spells", "south");
  add_exit("/d/damned/guilds/join_rooms/ranger_join", "up");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //    add_skill(string skill, int level, int flag)
  //    spell           The name of the skill which is being added
  //    level           The level at which the player may begin
  //                    developing the skill.
  //    flag            (optional)  If a non-zero number is supplied,
  //                    the skill will be considered "secondary" to
  //                    the guild and cost double to develop.

  add_skill("axe", 1);
  add_skill("consider", 1);
  add_skill("blade", 1);
  add_skill("two handed staff", 1);
  add_skill("knife", 1);
  add_skill("attack", 1);
  add_skill("parry", 1);
  add_skill("swimming", 1);
  add_skill("perception", 1);
  add_skill("thrown", 1);
  add_skill("woodland lore", 3);
  add_skill("illusionism", 3);
  add_skill("lumberjack",3);
  add_skill("carpentry", 3);
  add_skill("concentrate", 3);
  add_skill("herb lore",4);
  add_skill("dodge", 7);
  add_skill("repair weapon", 7);
  add_skill("offhand training", 10);
  add_skill("poison lore", 10);
  add_skill("skin corpse", 10);
  add_skill("leather craft",10);
  add_skill("dual attack", 15);
  add_skill("reverse stroke", 15);
  return;
}
void reset() {
  if(!present("guard"))
    new("/d/damned/guilds/ranger/rg_guard")->move(this_object());
  return;
}
