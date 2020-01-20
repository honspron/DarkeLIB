//	An example guildmaster for paladins.
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95

inherit "/std/guilds/npc_guildmaster";

//	He is set up identically to a monster.

void create() {
  object ob, ob2, ob3;

  ::create();

  //  The one difference is the following line:
  set_join_room("/d/damned/guilds/join_rooms/chaotic-lord_join");
  //  The above refers the guildmaster to the joining room, which
  //  handles all "book keeping"

  set("short", "Darkryl the Chaotic Lord Guildmaster");
  set("long", "As you look upon Darkryl he resembles a demon. "+
      "His skin is jet black and his face is scared from the bonding "+
      "of the demon to his skin.  You almost tremble when you look at " +
      " his face and see the horrors of his deeds.\n");
  set_level(21);
  set_max_hp(3500);
  set_hp(3500);
  set_max_mp(5000);
  set_mp(5000);
  set_property("base hp regen", 50);
  set_property("base mp regen", 20);
  set_gender("male");
  set("race", "human");
  set_body_type("human");
  set_id(({ "guildmaster", "darkryl", "chaotic lord guildmaster" }));
  //  NOTE:  It is important that, if you set_id, you include
  //  "guildmaster" as one of them.  If you do not set_id, he
  //  will still work.
  set_overall_ac(60);
  set_name("guildmaster");
  set_property("melee damage", ([ "crushing" : 40 ]));
  set_skill("melee", 80);
  set_skill("perception", 150);
  set_skill("dual attack", 120);
  set_skill("dodge", 150);
  set_skill("parry", 150);
  set_skill("chaos magic", 140);
  set_skill("blade", 200);
  set_stats("strength", 150);
  set_skill("attack", 150);
  set_spell_level("chaos ball",6);
  add_spell("chaos ball", "$A");
  set_spell_level("chaos storm", 6);
  add_spell("chaos storm", "$A");
  set_casting_chance(100);
  set_combat_chance(150);
  set_property("ambidextry",1);
  ob = new("/d/damned/guilds/chaotic-lord/chaotic-lord_sword");
  ob->move(this_object());
  ob3 = new("/d/damned/virtual/long-sword_6.weapon");
  ob3->move(this_object());
  ob2 = new("/d/damned/guilds/chaotic-lord/chaotic-lord_helm");
  ob2->move(this_object());
  force_me("equip");
  return;
}

int query_num_rounds() { return 3; }

