//	An example skill training room for the fighter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "The Nightblade's Spell Training Room");
  set("long", 
"This room, like the rest of the guild, is cloaked in "
"shadow.  Nightblades off various ages sit at small tables, "
"studying leather tomes by gaslight.  The various flickering "
"flames cast eerie shadows about the room, and you have the distinct "
"sensation of being stalked.\n");
  //  "\n" important here, too.

  set_property("light", -1);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/nightblade_join");

  set_exits( ([ "west" : "/d/damned/guilds/nightblade/train_room" ]) );
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

  add_spell("power word, stun");
  add_spell("clairvoyance");
  add_spell("power word, blind", 12, 1);
  add_spell("instill poison");
  add_spell("invisibility", 10);
  add_spell("alter visage");
  add_spell("improved invisibility");
  add_spell("poison weapon");
  add_spell("suggestion");
add_spell("stun blade");
  add_spell("gaseous form");
  add_spell("animal transformation");
  add_spell("summon illusionary guardian");
  add_spell("winged flight");
  add_spell("silent walk");
  add_spell("haste", 12);
  add_spell("area poison");
  add_spell("scry");
  add_spell("poison missile");
  add_spell("distance poison");
  add_spell("transport", 15, 1);
  add_spell("apportation");
  add_spell("blur");
  add_spell("mirror image");
  add_spell("darkness", 2);
  add_spell("dark vision", 2);
  add_spell("slow");
  add_spell("iron will");
  add_spell("body disruption");
  return;
}

  
