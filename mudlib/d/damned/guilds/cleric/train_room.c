//	An example skill training room for the fighter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  set_property("train noun", "meditations");
  set_property("train verb", "meditate");
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "cleric_board"}) );
  ob->set_board_id("cleric_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/cleric/train_room");
  ob->set("short","Cleric Board");
  ob->set("long","A board for players to post notes.\n");
  ob->set_edit_ok( ({"/d/damned/guilds/join_rooms/cleric_join"->query_master(),"zareth"}) );
  set("short", "The Clerics' Training Room");
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
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/cleric_join");

  set_exits( ([ "south" : "/d/damned/guilds/join_rooms/cleric_join",
	            "east"  : "/d/damned/guilds/cleric/cleric_spell_room",
	            "west"  : "/d/damned/guilds/cleric/c_treas",
                "up"    : "/d/damned/guilds/cleric/meditate",
                "down"  : "/d/damned/guilds/cleric/c_combat"
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
  add_skill("communion",3);
  add_skill("lay on hands", 2);
  return;
}

void reset() {
if(!present("guard"))
    new("/d/damned/guilds/cleric/t_guard")->move(this_object());
  return;
}
