//	This is the meditation room of the Seer Guild
//  It is a skill training room for non-physical skills
//
//	DarkeLIB 0.1
//	Zortek

inherit "/std/guilds/skill_room";

void init() {
  ::init();
  add_action("meditate","meditate");
}

void create() {
  object ob;
  ::create();
  set("short", "Meditation Chamber");
//  The above affect what commands the player uses to train and list
//  skills.

  set("long", @TEXT 
You immediately feel a sense of peace and tranquility wash over you
as you step off the final riser of the stairs.  The sweet perfume of
incense caresses your senses and fills your lungs with tranquility.

The floor is covered with pillows inviting medition and contemplation.
TEXT
);

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/seer_join");

  set_exits( ([ "down"  : "/d/damned/guilds/seer/rooms/main_room"
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

  add_skill("consider", 1);
  add_skill("trade lore", 1);
  add_skill("prospecting", 1, 1);
  add_skill("meditation", 1);
  add_skill("channeling", 1);

  add_skill("perception", 2);
  add_skill("herb lore", 2);
  add_skill("prepare item", 2);
  add_skill("psychokinesis", 2);
  
  add_skill("concentrate",3);
  add_skill("spell sense", 3);
  add_skill("psychometabolism", 3);
  add_skill("drugs", 3);
  
  add_skill("detect magic", 4);
  add_skill("mask identity", 4);
  add_skill("psychoportation", 4);
  
  add_skill("clairsentience", 5);
  return;
}

int can_exceed_max_mp() { return 1; }

int meditate(string str) {
  int x,y;
  if(!str) {
    y = this_player()->query_property("last meditate");
    if(y+800 < time()) {
      write("You sit quietly and contemplate.");
      return 1;
    }
    x = random(100);
    if(x >= (int)this_player()->query_skill("meditation")) {
      this_player()->add_mp(250);
      this_player()->set_property("last meditate", time());
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
}
