inherit "/std/guilds/npc_guildmaster";



void create() {

  object ob;



  ::create();

  set_join_room("/d/damned/guilds/join_rooms/seer_join");



  set("short", "Vergonna Merra, Great Oracle of Coralmoor");

  set("long", @TEXT

Vergonna sits before you calmly and doesn't seem to notice

your presence.  She is staring off into space with a glazed

look in her crystal blue eyes.

TEXT

);

  set_level(35);

  set_max_hp(2500);

  set_hp(2500);

  set_max_mp(30000);

  set_mp(30000);

  set_overall_ac(60);

  set_property("base mp regen", 140);

  set_property("base hp regen", 20);

  set_gender("male");

  set("race", "high-man");

  set_body_type("human");

  

  set_skill("perception", 250);

  set_skill("melee", 200);

  set_skill("dodge", 150);

  set_skill("parry", 150);

  set_skill("reverse stroke", 200);

  set_skill("concentrate", 200);

  

  set_stats("strength", 79);

  set_stats("intelligence", 240);

  set_stats("wisdom", 340);

  set_stats("dexterity", 210);

  

  set_spell_level("cause serious wounds", 6);

  add_spell("cause serious wounds", "$A");



  set_casting_chance(250);

  set_combat_chance(120);

  

  set_id(({ "vergonna", 

            "guildmaster", 

            "seer", 

            "seer guildmaster", 

            "oracle", 

            "great oracle",

         }));

  

  set_name("guildmaster");

  

  set_property("ambidextry", 1);

  set_property("melee damage", ([ "psychic" : 50, ]));

  

  set_languages(({ "common", }));

  ob = new("/d/damned/guilds/seer/items/gm_circlet");

  ob->move(this_object());

  force_me("wear circlet");

  ob = new("/d/damned/guilds/seer/items/gm_robe");

  ob->move(this_object());

  force_me("wear robe");

  return;

}



int query_num_rounds() { return 2; }

