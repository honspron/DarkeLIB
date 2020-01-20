//	An example skill training room for the necromancer's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void init() {
	::init();
	add_action("look_map", "look");
}
	
void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "necromancer_board"}) );
  ob->set_board_id("necromancer_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/necromancer/train_room");
  ob->set("short","Necromancer Board");
  ob->set("long", "A bulletin board the member of the guild use to pass notes.\n");
  set("short", "The Necromancers' Training Grounds");
   set("long", "The room that you now stand in, is a room of great wonder and morbidity.  All the walls of this room are covered with bones of the long dead.  Their bodies cover the walls in beautiful arches of the dead."+
	"  There is a treasury to the east of this room and a library to the west, each of the doorways that mark these rooms are covered with the limbs of the dead." +
	"  On the wall has been posted a city map of Kuril.\n");
  //  "\n" important here, too.
  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/necromancer_join");

  add_exit("/d/damned/guilds/join_rooms/necromancer_join", "north");
  add_exit("/d/damned/guilds/necromancer/n_treas", "east");
  add_exit("/d/damned/guilds/necromancer/necromancer_spell_room", "west");
  
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
  add_skill("detect magic", 6);
  add_skill("spell sense", 15);
  add_skill("necromancy", 1);
  add_skill("illusionism", 1);
  add_skill("perception", 1);
  add_skill("attack", 1);
  add_skill("melee", 1);
  add_skill("knife", 1);
  add_skill("fast casting", 12, 1);
  add_skill("focus casting", 5, 1);
  add_skill("consider", 1);
  add_skill("concentrate",5,1);
  add_skill("two handed staff", 1);
  add_skill("perception", 1);
  add_skill("swimming", 1);
  add_skill("prospecting", 1, 1);
  add_skill("dodge", 5);
  add_skill("control undead", 1);
  add_skill("prepare corpse", 1);
  return;
}

void reset() {
   ::reset();
   if(!present("guard"))  new("/d/damned/guilds/necromancer/t_guard")->
           move(this_object());
   return;
}

int look_map(string str) {
	if(!str) { return 0; }
	if( (str == "map") || (str == "city map") || (str == "at map") ) {
		this_player()->more("/d/nocte/kuril/history/necro_map");
		return 1;
	}
}
