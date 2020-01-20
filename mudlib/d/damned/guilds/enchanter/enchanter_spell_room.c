//	An example skill training room for the enchanter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "The Enchanters' Spell Training Room");
  set("long", 
"This is where enchanters study the spells that enable them to make "+
"wonderous machines and imbue objects with magical energy.\n");
  //  "\n" important here, too.

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/enchanter_join");

  set_exits( ([ "east" : "/d/damned/guilds/enchanter/train_room" ]) );
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

  add_spell("garguth's open palm");
  add_spell("garguth's grasping hand");
  add_spell("garguth's pounding fist");
  add_spell("prepare spell");
  add_spell("transmutation");
  add_spell("claimed weapon");
  add_spell("lock enchantment");
  add_spell("scribe scroll");
  add_spell("dispel rune");
  add_spell("activate powerstone");
  add_spell("icy weapon");
  add_spell("flame blade");
  add_spell("sense aura");
  add_spell("minor puissance");
  add_spell("major puissance");
  add_spell("minor accuracy");
  add_spell("major accuracy");
  add_spell("minor fortification");
  add_spell("major fortification");
  add_spell("true armour");
  add_spell("true weapon");
  add_spell("poison rune");
  add_spell("exploding rune");
  add_spell("healing rune");
  add_spell("gate rune");
  add_spell("summon rune");
  add_spell("transport rune");
  add_spell("delay rune");
  add_spell("preserve rune");
  add_spell("enchanter mark");
  add_spell("transport beacon");
  add_spell("fashion dragon engine");
  add_spell("fashion golem");
  add_spell("fashion statue");
  add_spell("improve dragon engine");
  add_spell("improve statue");
  add_spell("improve golem");
  add_spell("self power");
  add_spell("implosion");
  add_spell("energy shield");
  add_spell("shield of ithian");
  add_spell("armour of oblivion");
  add_spell("force shield");
  return;
}






