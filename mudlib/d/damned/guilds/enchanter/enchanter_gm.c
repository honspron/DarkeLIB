//	An example guildmaster for enchanters.
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95

inherit "/std/guilds/npc_guildmaster";

//	He is set up identically to a monster.

void create() {
  object ob, ob2;

  ::create();

  //  The one difference is the following line:
  set_join_room("/d/damned/guilds/join_rooms/enchanter_join");
  //  The above refers the guildmaster to the joining room, which
  //  handles all "book keeping"

  set("short", "Geesh, the Enchanter Guildmaster");
  set("long", "Geesh is clad in simple robes and looks unassuming, more  "+
      "interested in his gadgets and magical formulae than in striking "+
      "a pose.  The only unusual thing you see is the strange amulet that "
      "he is wearing\n");
  set_level(20);
  set_max_hp(2500);
  set_hp(2500);
  set_max_mp(4000);
  set_mp(4000);
  set_overall_ac(60);
  set_property("base hp regen", 50);
  set_property("base mp regen", 100);
  set_gender("male");
  set("race", "gnome");
  set_body_type("human");
  //  NOTE:  It is important that, if you set_id, you include
  //  "guildmaster" as one of them.  If you do not set_id, he
  //  will still work.
  set_id(({ "guildmaster", "enchanter", "enchanter guildmaster", "geesh" }));
  set_name("guildmaster");
  set_property("melee damage", ([ "crushing" : 30 ]));
  set_skill("melee", 120);
  set_skill("perception", 150);
  set_skill("dodge", 150);
  set_skill("parry", 120);
  set_stats("strength", 130);
  set_skill("attack", 120);
  set_skill("two handed staff", 150);
  set_skill("enchantment", 90);
  set_spell_level("garguth's pounding fist", 6);
  add_spell("garguth's pounding fist", "$A");
  set_skill("conjuration", 75);
  add_spell("blizzard", "", 1);
  set_spell_level("blizzard", 5);
  set_combat_chance(150);
  set_property("ambidextry",1);
  ob = new("/d/damned/guilds/enchanter/gm_amulet");
  ob->move(this_object());
  force_me("wear amulet");
  ob2 = new("/d/damned/guilds/enchanter/gm_staff");
  ob2->move(this_object());
  force_me("wield staff in right hand and left hand");
  return;
}

int query_num_rounds() { return 3; }

string query_element() { return "chaos"; }




























