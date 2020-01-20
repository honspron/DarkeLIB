//	An example guildmaster for fighters.
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95

inherit "/std/guilds/npc_guildmaster";

//	He is set up identically to a monster.

void create() {
  object ob;

  ::create();

  //  The one difference is the following line:
  set_join_room("/d/damned/guilds/join_rooms/fighter_join");
  //  The above refers the guildmaster to the joining room, which
  //  handles all "book keeping"

  set("short", "The Fighter Guildmaster");
  set("long", "The Guildmaster is very impressive.  He looks like he "+
      "could beat up just about anyone or anything on the mud.");
  set_level(16);
   set_max_hp(6000);
   set_hp(6000);
   set_overall_ac(75);
  set_property("base hp regen", 80);
  set_gender("male");
  set("race", "human");
  set_body_type("human");
  set_id(({ "guildmaster", "fighter", "fighter guildmaster" }));
  //  NOTE:  It is important that, if you set_id, you include
  //  "guildmaster" as one of them.  If you do not set_id, he
  //  will still work.
  set_name("guildmaster");
  set_property("melee damage", ([ "crushing" : 20 ]));
  set_skill("melee", 80);
   set_skill("perception", 200);
  set_skill("dodge", 16);
   set_skill("parry", 150);
  set_skill("two handed blade", 250);
  set_stats("strength", 200);
  set_skill("attack", 200);
  ob = new("/d/damned/guilds/fighter/gm_sword");
  ob->move(this_object());
  force_me("equip");
  return;
}

int query_num_rounds() { return 3; }
