//	Primary Training Room for the Cleric Guild
//  Utilizing v2.0 Guild System
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/d/damned/guilds/cleric/med_room";
#define GUILD_NAME "cleric"
#define DOMAIN     "/d/damned/guilds/cleric_new/"

void create() {
  object ob;
  ::create();

  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "cleric_board"}) );
  ob->set_board_id("cleric_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/cleric/train_room");
  ob->set("short","Cleric Board");
  ob->set("long","A board for players to post notes.\n");

  set("short", "Grand Cloister");
  set("long", @TEXT 
You have entered the Grand Cloister.  The interior is highly decorated
with painting, sculpture, and mosiac artwork.  Three chandeleers hosting
thousands of candles light the area majestically.  A grand alter, centered
along the northern wall, contains the the Chalice of the Holy, the Book of
Sanctity, and the Orb of Wisdom.  There is an archway to the east, leading
to the shrine of heavenly gifts, and to the the west, His blessed archive.
An alabaster stairway here is watched by beautiful ivory cherubim and
seraphim banister supports.
TEXT
);

  set_property("light", 3);
  set_property("indoors", 1);
  
  set_exits( ([ "south" : DOMAIN+"cl_join",
	            "east"  : DOMAIN+"cl_spell",
	            "west"  : DOMAIN+"cl_treas",
                "up"    : DOMAIN+"meditate",
                "down"  : DOMAIN+"cl_cbt",
           ]));
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	spell 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("prayer", 1);
  add_skill("body alteration", 1);
  add_skill("lay on hands", 3, 1);
  return;
}

void reset() {
  if(!present("monk"))
    new(DOMAIN+"cl_guard")->move(this_object());
  return;
}
