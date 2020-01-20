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

  add_spell("cure light wounds", 1);
  add_spell("satisfy thirst", 1);
  add_spell("satisfy hunger", 1);
  add_spell("holy light", 1);

  add_spell("cause light wounds", 2);
  add_spell("divine might",2);
  add_spell("remove poison", 2);

  add_spell("protection from chaos", 3);
  add_spell("preserve corpse", 3);
  add_spell("intoxication", 3);
  add_spell("holy word", 3);

  add_spell("holy armour", 4);
  add_spell("cure serious wounds", 4);
  add_spell("create food", 4);

  add_spell("cause serious wounds", 5);
  add_spell("summon aerial servant", 5);

  add_spell("summon ethereal entity", 6);
  add_spell("instill poison", 6);
  add_spell("sanctuary", 6);

  add_spell("combat healing", 7);
  add_spell("cure critical wounds", 7);
  add_spell("hand of the divine", 7);

  add_spell("cause critical wounds", 8);
  add_spell("call divine strength", 8);

  add_spell("create elixir of healing", 9);
  add_spell("armour of faith", 9);

  add_spell("divine transformation", 10);
  add_spell("heal", 10);

  add_spell("harm", 11);
  add_spell("regeneration", 11);
  add_spell("summon guardian angel", 11);

  add_spell("distance healing", 12);
  add_spell("resurrect", 12);
  add_spell("increase metabolism", 12);

  add_spell("smite", 13);
  add_spell("decrease metabolism", 13);

  add_spell("distance harming", 14);
  add_spell("create alabaster potion", 14);
  add_spell("summon elder seraph", 14);

  add_spell("mass heal", 15);
  add_spell("scales of justice", 15);

  add_spell("true heal", 16);

  add_spell("soul gate", 17);

  add_spell("summon arch angel", 18);

  add_spell("bolt of righteousness", 19);

  add_spell("holy mission", 20);

  add_spell("wrath of god", 25);
  return;
}

  
