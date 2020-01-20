//	This is the prayer room for the Cleric Guild
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95
//  Zortek

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "Prayer room for the Holy Order of Clerics");
  set("long", @TEXT
This is where clerics study vast amounts of religious texts in order
to master the various spells available to them.
TEXT
);
  set_property("light", 3);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/cleric_join");

  set_exits( ([ "west" : "/d/damned/guilds/cleric/train_room" ]) );
  //  All the rest is adding the spells.  The add_skill lines are of the
  //  following form:
  //  	add_spell(string spell, int level, int flag)
  //	spell 		The name of the spell which is being added
  // 	level		(optional) The level at which the player may begin
  //			developing the spell.  If not supplied,
  //			the default level is used.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_spell("cause light wounds", 2);
  add_spell("divine might",2);
  add_spell("intoxication", 3);
  add_spell("cause serious wounds", 5);
  add_spell("instill poison", 6);
  add_spell("combat healing", 7);
  add_spell("cause critical wounds", 8);
  add_spell("call divine strength", 8);
  add_spell("armour of faith", 9);
  add_spell("harm", 11);
  add_spell("regeneration", 11);
  add_spell("smite", 13);
  add_spell("decrease metabolism", 13);
  add_spell("distance harming", 14);
  add_spell("scales of justice", 15);
  return;
}

  
