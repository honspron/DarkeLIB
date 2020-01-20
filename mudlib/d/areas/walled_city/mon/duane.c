inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("duane");
   set("id", ({"shopkeeper", "shop keeper", "Duane"}));
   add_money("gold", 3500);
   set_level(50);
   set_exp(5000);
   set_max_hp(10000000);
   set_hp(10000000);
   set_property("enhance criticals", -10);
   set_property("melee damage", ([ "crushing" : 99]));
   set("short","Duane, the shopkeeper");
   set("long",
"Duane is a stout, burly dwarf.  He is a huge man with an amiable "
"grin.  He looks like he wants to sell you something.");
   set_gender("male");
   set_body_type("human");
   set("race", "high-man");
   set_skill("elementalism", 195);
   set_spell_level("elemental storm", 6);
   add_spell("elemental storm", "");
   set_combat_chance(90);
   set_skill("dodge", 70);
   set_skill("parry", 80);
   set_skill("martial arts", 125);
   set_skill("perception", 95);
   set_languages(({"common", "stormspeak", "elvish", "serra", "yin", "dwarvish",
                "drow", "pix", "treefolk", "vr'krr", "middle-english",
		"catfolk","undead-tongue", "hisaaa", "ogryn" }));
   set("storage room","/d/damned/akkad/shops/shop4_store");
   set_stats("dexterity", 150);
   set_stats("strength", 200);
   set("num rounds", 4);
   set("markup", 50);
}
