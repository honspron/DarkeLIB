// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from train_room.c code
// 10/05/96

//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  ::create();
  set("short", "Chamber of Knowledge");
  set("long", 
	"Books, maps, and other objects of learning fill the room.  It is "
	"here that the Priests of K'thach come to learn skills that will "
	"aid them in their worldly travels.\n");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");

  add_exit("/d/damned/guilds/war-priest/hh5", "west");
  add_exit("/d/damned/guilds/war-priest/hh9", "south");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("trade lore", 1, 1);
  add_skill("body alteration", 2);
  add_skill("swimming",1);
  add_skill("prospecting", 1, 1);
  add_skill("compare", 3, 1);
  add_skill("perception", 1, 1);
  add_skill("consider", 1);
  return;
}
