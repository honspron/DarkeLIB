//	An example skill training room for the fighter's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "Chamber of Spell Training");
  set("long", 
	"Lining the walls are books, scrolls, and ancient tomes of lore "
	"and religious works.  It is here that the Priests of K'thach come "
	"to learn more of their god.\n");
  //  "\n" important here, too.

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");

  set_exits( ([ "west" : "/d/damned/guilds/war-priest/hh2" ]) );
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

  add_spell("hammer of k'thach");
  add_spell("holy word", 1);
  add_spell("hand of the divine");
  add_spell("battle aura");
  add_spell("rain of spears");
  add_spell("wrath of god");
  add_spell("create food",5);
  add_spell("preserve corpse");
  add_spell("combat healing");
add_spell("retribution of k'thach", 14);
  add_spell("vengeance of k'thach", 26);
  add_spell("protection from chaos", 5);
  add_spell("shields of war");
  add_spell("divine might");
  add_spell("remove poison",6);
  add_spell("instill poison",6);
  add_spell("summon ethereal entity",7);
  add_spell("holy light");
  add_spell("holy armour", 7);
  add_spell("armour of faith", 13, 1);
  add_spell("call divine plate");
  add_spell("call hammer of faith");
  add_spell("call spirit sword");
  add_spell("call blade of k'thach");
  add_spell("war-hewn weapon");
  add_spell("battle fury");
  add_spell("satisfy thirst",2);
  add_spell("satisfy hunger",2);
  add_spell("intoxication",4);
  add_spell("create elixir of healing");
  add_spell("warrior's interment");
  add_spell("regeneration");
  add_spell("summon aerial servant");
  add_spell("indomitable spirit");
  return;
}
