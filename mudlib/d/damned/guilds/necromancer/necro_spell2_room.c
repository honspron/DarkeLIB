//	An example skill training room for the necromancer's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "The Crypt of the Necromancers' Guild");
  set("long", 
"This is the under-ground crypt of the Necromancers' Guild.  The Crypt is one enormous cavern decorated with skulls and bones of various creatures.  Along the sides of the room are a few jars of embalming liquid and body parts.  The Crypt itself has many wooden tables with leather straps for you to animate your various undead legions.  Off to the far end of the crypt is the fabled Necronomicon, a book of immense power and knowledge.  You will be able to learn the secrets of the Necronomicon in this Crypt.
");
  //  "\n" important here, too.

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/necromancer_join");

  set_exits( ([ "up" : "/d/damned/guilds/necromancer/necromancer_spell_room" ]) );
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

  add_spell("animate skeleton");
  add_spell("animate ghast");
  add_spell("animate ghoul");
  add_spell("animate vampire");
  add_spell("animate zombie");
  add_spell("animate death knight");
  add_spell("animate lich");
  add_spell("animate demilich");
  add_spell("animate dracolich");
  return;
}






