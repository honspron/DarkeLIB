//	An example skill training room for the nightblade's guild.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";
  object ob;
void create() {
  ::create();
  set("short", "The nightblades' Training Room");
  set("long", "This is a truly intimidating room.  The dark is "
  "oppressive, and several cloaked figures slide about smoothly.  "
  "No faces are seen.  Though you see nothing, you hear the sounds of "
  "nightblades honing their skills...a dull thud there, a ripping sound here.  "
  "\nTo the west is the treasury.  The fee for entry is 5 silver per level.");
  //  "\n" important here, too.
  set_property("light", -1);
  set_property("indoors", 1);
  
  //  The following line is VERY, VERY important.
  set_join_room("/d/damned/guilds/join_rooms/nightblade_join");

ob = new("std/bboard");
ob->set_name("board");
ob->set_id( ({"board", "nightblade board"}) );
ob->set_board_id("nightblade_board");
ob->set_max_posts(25);
ob->set_location("d/damned/guilds/nightblade/train_room");
ob->set("short","Nightblade Board");
ob->set("long", "A board for players to post notes.\n");

  add_exit("/d/damned/guilds/join_rooms/nightblade_join", "north");
  add_exit("/d/damned/guilds/nightblade/n_treas", "west");
  add_exit("/d/damned/guilds/nightblade/nightblade_spell_room", "east");
  
  //  All the rest is adding the skills.  The add_skill lines are of the
  //  following form:
  //  	add_skill(string skill, int level, int flag)
  //	skill 		The name of the skill which is being added
  // 	level		The level at which the player may begin
  //			developing the skill.
  //	flag		(optional)  If a non-zero number is supplied,
  //			the skill will be considered "secondary" to
  //			the guild and cost double to develop.

  add_skill("trade lore", 1);
  add_skill("prospecting", 1, 1);
  add_skill("consider", 1);
  add_skill("swimming", 1);
  add_skill("attack", 1);
  add_skill("melee", 3);
  add_skill("parry", 1);
  add_skill("dodge", 1);
  add_skill("blade", 1);
  add_skill("knife", 1);
  add_skill("offhand training", 10, 1);
  add_skill("dual attack", 17, 1);
  add_skill("concentrate", 3);
  add_skill("flail", 1);
  add_skill("blunt", 1);
  add_skill("detect magic", 7);
  add_skill("magery", 1);
  add_skill("illusionism", 1);
  add_skill("body alteration", 1);
  add_skill("back stab", 6);
  add_skill("assassination", 20);
  add_skill("reverse stroke", 15);
  add_skill("perception", 1);
  add_skill("stalk", 10);
  add_skill("shadow", 19, 1);
  add_skill("spell sense", 17, 1);
  add_skill("compare", 3);
  return;
}

void reset() {
  ::reset();
  if (!present("guard"))
      new("/d/damned/guilds/nightblade/t_guard")->move(this_object());
  return;
}





