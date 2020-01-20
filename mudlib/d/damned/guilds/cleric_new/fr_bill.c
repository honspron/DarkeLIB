inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("bill");
   set("id", ({"shopkeeper", "shop keeper", "bill"}));
   set_level(12);
   set("short","Father Bill, the shopkeeper");
   set("long",
"Father Bill tends the shop here.  He seems very helpful.");
   set_gender("male");
   set_body_type("human");
   set("race", "high-man");
  set_property("melee damage", ([ "crushing" : 45]));
  set_overall_ac(30);
  set_skill("prayer", 80);
  set_stats("wisdom", 120);
  set_spell_level("harm", 4);
  set_spell_level("decrease metabolism", 4);
  set_spell_level("cure serious wounds", 6);
  set_skill("concentrate", 100);
  set("concentrate", 1);
  add_spell("harm", "$A");
  add_spell("decrease metabolism", "$A");
  add_spell("cure serious wounds", "$(ME)");
  set_max_mp(1200);
  set_max_hp(1000);
  set_hp(1000);
  set_mp(1200);
   set_skill("melee", 70);
   set_skill("dodge", 70);
   set_skill("perception", 70);
   set_overall_ac( 5 );
   set_languages(({"common", "elvish", "treefolk", "serra", "yin", "dwarvish"}));
   set("storage room","/d/damned/guilds/cleric/shop_store");
   set("no sell", 1);
   set("markup", 20);
}
