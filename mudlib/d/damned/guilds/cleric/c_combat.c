//	Meditation room for Combat skills for Clerics
//
//	DarkeLIB 0.1
//	Zortek

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  set("short", "Defense of the Faith Chamber");
  set_property("train verb", "meditate");
  set_property("train noun", "meditations");
  set("long", @TEXT 
You have entered the meditation chamber of martial enlightenment.  Here
you may seek gifts in His name for the purpose of defending the faith
cleansing the impure.  An alabaster stairway here is watched by beautiful
ivory cherubim and seraphim banister supports.

TEXT
);

  set_property("light", 3);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/cleric_join");

  set_exits( ([ "up"    : "/d/damned/guilds/cleric/train_room",
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

  add_skill("blunt", 1);
  add_skill("swimming",1);
  add_skill("attack", 1, 1);

  add_skill("two handed blunt", 2);
  add_skill("body block", 2);

  add_skill("flail", 3, 1);
  add_skill("melee", 3, 1);

  add_skill("two handed flail", 4, 1);

  add_skill("compare", 5, 1);

  add_skill("dodge", 6, 1);

  add_skill("parry", 7, 1);


  return;
}

int meditate(string str) {
  int x;
  if(!str) {
    x = random(100);
    if(x >= (int)this_player()->query_skill("prayer")*2) {
      this_player()->add_mp(100);
      write(@TEXT
Finding a pleasant spot, you situate yourself comfortably and meditate
on the meaning of life.  You find an inner peace and tranquility that
centers your awareness on the truth, honesty, and love.
TEXT
);
    return 1;
    }
    else {
      this_player()->add_mp(1);
      write(@TEXT
You find a comfortable spot and begin to meditate on the meaning of
life.  Center you spirit and feel a sense of joy and happiness.
TEXT
);
    return 1;
    }
  }
  ::train_skill(str);
}
