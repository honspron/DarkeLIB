//	An example guildmaster for arch magi.
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95

inherit "/std/guilds/npc_guildmaster";

//	He is set up identically to a monster.

void create() {
  object ob;

  ::create();

  //  The one difference is the following line:
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");
  //  The above refers the guildmaster to the joining room, which
  //  handles all "book keeping"

  set("short", "Jun Khal, the War Priest Guildmaster");
  set("long", 
"Jun Kahl is a tall Ent, wearing ornate robes and various decorations about "
"his branches.  He is an impressive display of both apparent friendliness and "
"inrcredible might!");
  set_level(19);
  set_max_hp(3800);
  set_hp(3800);
  set_max_mp(4000);
  set_mp(4000);
  set_property("base mp regen", 140);
  set_property("base hp regen", 80);
  set_gender("male");
  set("race", "ent");
  set_body_type("ent");
  set_skill("prayer", 90);
  set_id(({ "jun khal", "guildmaster", "war-priest", "jun", "war-priest guildmaster" }));
  //  NOTE:  It is important that, if you set_id, you include
  //  "guildmaster" as one of them.  If you do not set_id, he
  //  will still work.
  set_name("guildmaster");
  //  The name MUST be set to guildmaster if you want tell's to work.
  set_property("melee damage", ([ "crushing" : 50 ]));
  set_overall_ac(45);
  set_skill("perception", 150);
  set_skill("body alteration", 150);
  set_skill("melee", 90);
  set_skill("dodge", 150);
  set_skill("parry", 100);
  set_skill("two handed blunt", 200);
  set_stats("strength", 200);
  set_stats("intelligence", 140);
  set_skill("attack", 160);
  set_languages(({ "common", "serra", "yin", "treefolk", "catfolk", "elvish",
		"dwarvish", "drow", "grken", "middle-english", "stormspeak" }));
  set_spell_level("harm",6);
  add_spell("harm", "$A");
  set_spell_level("bolt of righteousness", 6);
  add_spell("bolt of righteousness", "$A");
  set_spell_level("cure serious wounds", 6);
  add_spell("cure serious wounds", "$(ME)");
  set_spell_level("heal", 5);
  add_spell("heal", "$(ME)");
  set_spell_level("scales of justice", 4);
  add_spell("scales of justice", "$(ME)", 1, 100);
  set_spell_level("cause critical wounds", 6);
  add_spell("cause critical wounds", "$A");
  set_spell_level("armour of faith", 6);
  add_spell("armour of faith", "$(ME)", 1, 200);
  set_spell_level("wrath of god", 4);
  add_spell("wrath of god", "$A");
  set_combat_chance(120);
  set_property("ambidextry", 1);
  ob = new("/d/damned/guilds/war-priest/gm_ankh");
  ob->move(this_object());
  force_me("wear ankh");
  ob = new("/d/damned/virtual/war-hammer_6.weapon");
  ob->set_property("enchantment", 15);
  ob->set_property("enhance criticals", 1);
  ob->set_property("hit bonus", 10);
  ob->move(this_object());
  force_me("wield hammer in first branch and second branch");
  return;
}

