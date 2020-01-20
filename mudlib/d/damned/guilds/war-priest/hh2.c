// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from train_room.c code
// 10/05/96

//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  ::create();
  set("short", "The war-priests' Training Room");
  set("long", 
	"An altar to K'thach rests in the center of this room.  Nothing "
	"more than a large slab of stone with a bowl shaped recess in the "
	"middle, it is constantly filled with offerings.\n"); 
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");

  add_exit("/d/damned/guilds/war-priest/hh1", "west");
  add_exit("/d/damned/guilds/war-priest/hh3", "east");
  add_exit("/d/damned/guilds/war-priest/hh5", "south");
  
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
  return;
}
