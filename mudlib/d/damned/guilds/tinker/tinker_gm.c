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
  set_join_room("/d/damned/guilds/join_rooms/tinker_join");
  //  The above refers the guildmaster to the joining room, which
  //  handles all "book keeping"

  set("short", "Julia, the Tinker Guildmaster");
  set("long", 
"Julia is an improbably attractive female high-man.  She wears "
"gray, coarse woven suspenders over a tightly-muscled physique.  "
"Long red hair and gentle features contrast with the frimness of her "
"musculature.");
  set_level(20);
  set_max_hp(10000);
  set_hp(10000);
  set_property("base mp regen", 5);
  set_property("base hp regen", 500);
  set_gender("female");
  set("race", "high-man");
  set_body_type("human");
  set_id(({ "julia", "guildmaster", "tinker", "tinker guildmaster" }));
  //  NOTE:  It is important that, if you set_id, you include
  //  "guildmaster" as one of them.  If you do not set_id, he
  //  will still work.
  set_name("guildmaster");
  //  The name MUST be set to guildmaster if you want tell's to work.
  set_property("melee damage", ([ "crushing" : 50 ]));
  set_skill("perception", 150);
  set_skill("melee", 130);
  set_skill("two handed blunt", 210);
  set_skill("blunt", 130);
  set_skill("dodge", 150);
  set_skill("parry", 120);
  set_stats("strength", 200);
  set_stats("intelligence", 100);
  set_skill("attack", 180);
  set_languages(({ "common", "serra", "yin", "treefolk", "catfolk", "elvish",
		"dwarvish", "drow", "mountainspeak", "undead-tongue", "middle-english", "stormspeak",
		  "ogryn", "orcish" }));
  set_property("ambidextry", 1);
  ob = new("/d/damned/guilds/tinker/gm_hammer");
  ob->move(this_object());
  force_me("wield hammer in right hand and left hand");
  ob = new("/d/damned/virtual/iron-greaves.armour");
  ob->set_property("enchantment", 10);
  ob->set_property("enhance criticals", -1);
  ob->move(this_object());
  force_me("wear greaves");
  set_overall_ac(75);
  return;
}

