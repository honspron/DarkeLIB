inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("samual");
   set("id", ({"shopkeeper", "shop keeper", "samual"}));
   set_level(45);
   set("short","Friar Samual, the shopkeeper");
   set("long", @TEXT
Friar Samual minds the modest shop of the Holy Church.
He seems helpful and kind, although he is a bit quiet.
TEXT
);
  set_gender("male");
  set_body_type("human");
  set("race", "high-man");
  set_property("melee damage", ([ "holy" : 45]));
   set_overall_ac(2000);
  set_stats("wisdom", 120);
  set_property("enhance criticals",-10);
  set_skill("defense", 100);
  set_skill("martial arts", 285);
  set_skill("parry",250);
  set_skill("prayer", 180);
  set_skill("melee", 70);
  set_skill("dodge", 70);
  set_skill("perception", 250);
  set_skill("concentrate", 100);
  set("concentrate", 1);
  
  set_combat_chance(100);
  set_spell_level("harm", 6);
  set_spell_level("decrease metabolism", 4);
  set_spell_level("cure serious wounds", 6);
  add_spell("harm", "$A");
  add_spell("decrease metabolism", "$A");
  add_spell("cure serious wounds", "$(ME)");
  
  set_max_mp(3000);
  set_max_hp(3000);
  set_hp(3000);
  set_mp(3000);
  
  set_languages(({"common", "elvish", "treefolk", "serra", "yin", "dwarvish", "pix", "catfolk",}));
  set("storage room","/d/damned/guilds/cleric/shop_store");
  set("markup", 35);
}
