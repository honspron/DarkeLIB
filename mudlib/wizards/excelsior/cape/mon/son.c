// /wizards/excelsior/cape/mon/son
// Excelsior 9-26-96
// have a nice day


inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("bob jr.");
   set("id", ({"jr","jr.","bob jr.","bob","shopkeeper", "shop keeper"}));
    add_money("gold", 3500);
   set_level(10);
   set_exp(1000000);
   set_max_hp(10000000);
   set_hp(10000000);
   set_property("enhance criticals", -10);
   set_property("melee damage", ([ "crushing" : 99]));
   set("short","Bob Jr.");
   set("long",
"This is the first born son of the infamous shop keeper Bob. He will help you "+
"with your shopkeeping needs if only you ask him for it.");
   set_gender("male");
   set_body_type("human");
   set("race", "high-man");
   set_skill("elementalism", 75);
   set_spell_level("elemental storm", 6);
   add_spell("elemental storm", "");
   set_combat_chance(80);
   set_skill("dodge", 70);
   set_skill("parry", 80);
   set_skill("martial arts", 50);
   set_skill("perception", 95);
   set_languages(({"common", "elvish", "serra", "yin", "dwarvish",
                "drow", "treefolk", "vr'krr", "middle-english",
		"catfolk","undead-tongue", "hisaaa" }));
   set("storage room","/wizards/excelsior/cape/storage/shop_store");
   set_stats("dexterity", 150);
   set_stats("strength", 200);
   set("num rounds", 2);
   set("markup", 45);
}
