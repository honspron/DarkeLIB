inherit "/std/guilds/spell_room";

void create() {
  ::create();
   set("short", "The Ranger's Spell Training Room");
  set("long", "This room is a vast library, in which the master spell books
are kept for rangers to study from. There is nothing very interesting in
this room but the books.");
  //  "\n" important here, too.

  set_property("light", 2);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
set_join_room("/d/damned/guilds/join_rooms/ranger_join");

  add_exit("rg_skills", "north");
  //  All the rest is adding the spells.  The add_skill lines are of the
  //  following form:
  //    add_spell(string spell, int level, int flag)
  //    spell           The name of the spell which is being added
  //    level           (optional) The level at which the player may begin
  //                    developing the spell.  If not supplied,
  //                    the default level is used.
  //    flag            (optional)  If a non-zero number is supplied,
  //                    the skill will be considered "secondary" to
  //                    the guild and cost double to develop.
add_spell("summon woodland familiar");
add_spell("invisibility",15);
add_spell("light of day",3);
add_spell("dark of night",3);
add_spell("infravision",3);
add_spell("bear's strength",9);
add_spell("blur",7);
add_spell("entangle",7);
add_spell("way of the ranger",20);
add_spell("hawk eyes",10);
add_spell("fox's agility",12);
add_spell("strength in numbers",12);
add_spell("detection",15);
add_spell("ranger animal transformation",9);
add_spell("stone blade",10);
add_spell("animate wood",25);
add_spell("revitalization",16);

add_spell("rejuvination",4);
  return;
}
