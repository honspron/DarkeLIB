//	This is the meditation room of the Cleric Guild
//  It is a skill training room for non-physical skills
//
//	DarkeLIB 0.1
//	Zortek

inherit "/d/damned/guilds/cleric/med_room";

void create() {
  object ob;
  ::create();
  set("short", "Spiritual Meditation Chantry");
  set("long", @TEXT 
You immediately feel a sense of peace and tranquility wash over you
as you step off the final riser of the stairs.  The sweet perfume of
incense caresses your senses and fills your lungs with purity.  The
presence of His spirit surrounds you with love and serenity.  Pillows,
overstuffed chairs, floor mats and pallets dot the chantry inviting
medition and contemplation.  An alabaster stairway here is watched by
beautiful ivory cherubim and seraphim banister supports.

TEXT
);

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/cleric_join");

  set_exits( ([ "down"  : "/d/damned/guilds/cleric/train_room"
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

  add_skill("perception", 2);

  add_skill("herb lore", 3);

  add_skill("detect magic", 4);

  add_skill("concentrate",5);

  add_skill("spell sense", 7);

  add_skill("resist stun", 10);
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
