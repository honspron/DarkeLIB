//	An example skill training room for the fighter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95
//
//      Edited by Tailwind
//
//      Blessed ReturnLIB
//      Tailwind 10/28/98

#include <std.h>
#include <../merc.h>

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "mercenary_board"}) );
  ob->set_board_id("mercenary_board");
  ob->set_max_posts(25);
  ob->set_location(ROOMS+"train_room");
  ob->set("short","Mercenary Board");
  ob->set("long","A board for players to post notes.\n");
  set("short", "The Mercenaries' Training Room");
  set("long", "This is the room where mercenaries come to practice their "+
        "combat and stealth skills.\nTo the east is the treasury.  A donation of "+
"5 silver per level is required to enter, but you may store items there.");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/mercenary_join");

  set_exits( ([ "south" : "/d/damned/guilds/join_rooms/mercenary_join",
                "east" : ROOMS+"m_treas" ]));
  
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
  add_skill("consider", 1);  
  add_skill("trade lore", 1, 1);
  add_skill("attack", 1);
  add_skill("melee", 1);
  add_skill("parry", 1);
  add_skill("block", 1);
  add_skill("prospecting", 1, 1);
  add_skill("blunt", 1);
  add_skill("flail", 1);
  add_skill("axe", 1);
  add_skill("knife", 1);
  add_skill("thrown", 1);
  add_skill("perception", 1);
  add_skill("swimming", 1);
  add_skill("body block", 1);
  add_skill("power slam", 2);
  add_skill("offhand training", 3);
  add_skill("dual attack", 5);
  add_skill("compare", 3);
  add_skill("shield bash", 3);
  add_skill("dodge", 3);
  add_skill("backhand smash", 4);
  add_skill("strong arm",5);
  add_skill("combo", 5);
  add_skill("limb breaker", 6);
  add_skill("knee",8);
  add_skill("combat awareness", 9);
  add_skill("reverse stroke", 10);
  add_skill("resist stun", 10);
  add_skill("sneak attack",13);
  add_skill("true strike",14);
  return;              
}

void reset() {
  ::reset();
  if(!present("guard", this_object()))
    new(MON+"t_guard")->move(this_object());
  return;
}

  
