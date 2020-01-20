//  Guildmaster for the Holy Church.
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95
//  Zortek 6/1/96

inherit "/std/guilds/npc_guildmaster";

void create() {
  object ob;

  ::create();

  set_join_room("/d/damned/guilds/join_rooms/cleric_join");

  set("short", "Pope Philip III, Leader of the Holy Church");
  set("long", @TEXT
The Pope looks upon you warmly.  He is an aging Ent, and his
form comforts you.
TEXT
);
  set_level(20);
  set_max_hp(3500);
  set_hp(3500);
  set_max_mp(3000);
  set_mp(3000);
  set_overall_ac(60);
  set_property("base mp regen", 140);
  set_property("base hp regen", 20);
  set_gender("male");
  set("race", "ent");
  set_body_type("ent");
  
  set_skill("perception", 150);
  set_skill("melee", 200);
  set_skill("dodge", 150);
  set_skill("parry", 150);
  set_skill("blunt", 87);
  set_stats("strength", 79);
  set_stats("wisdom", 140);
  set_skill("attack", 200);
  set_skill("body alteration", 90);
  set_skill("prayer", 90);
  
  set_spell_level("decrease metabolism", 6);
  add_spell("decrease metabolism", "$A");
  set_spell_level("cure light wounds", 6);
  add_spell("cure light wounds", "$R");
  set_spell_level("cure serious wounds", 6);
  add_spell("cure serious wounds", "$(ME)");
  set_spell_level("heal", 6);
  add_spell("heal", "$(ME)");
  set_spell_level("harm", 6);
  add_spell("harm", "$A");
  set_spell_level("cause serious wounds", 6);
  add_spell("cause serious wounds", "$A");
  set_casting_chance(10);
  set_combat_chance(120);
  
  set_id(({ "philip", "guildmaster", "cleric", "cleric guildmaster", "pope" }));
  
  set_name("guildmaster");
  
  set_property("ambidextry", 1);
  set_property("melee damage", ([ "crushing" : 50, "holy" : 30 ]));
  set_languages(({ "common", "serra", "yin", "treefolk", "catfolk",
                   "elvish", "dwarvish", "undead-tongue", "rachk",
                   "gnollish", "stormspeak", }));
  
  ob = new("/d/damned/guilds/cleric/gm_cross");
    ob->set_property("enchantment", 15);
    ob->set_property("enhance criticals", 1);
    ob->set_property("hit bonus", 10);
    ob->move(this_object());
  force_me("wear cross");
  return;
}

int query_num_rounds() { return 2; }
