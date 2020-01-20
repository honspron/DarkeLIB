#include "../daybreak.h"
inherit "/std/npc_shop";

void create() {
  object ob;

   ::create();
   set_name("gil");
   set("id", ({"gil", "shopkeeper", "shop keeper"}));
   add_money("gold", 5000);
   set_level(10);
   set_property("enhance criticals", -10);
   set_hp(200000);
   set_max_hp(200000);
   set_exp(1000000);
   set("short","Gil, the chest maker");
   set("long",
"Gil is a squat dwarf with beaded sweat on his brow.");
   set_skill("elementalism", 175);
   set_spell_level("elemental storm", 6);
   add_spell("elemental storm", "");
   set_combat_chance(80);
   set_gender("male");
   set_body_type("human");
   set("race", "dwarf");
   set_overall_ac(666);
   set_stats("strength", 305);
   set_stats("dexterity", 95);
   set_skill("two handed polearm", 190);
   set_skill("dodge", 170);
   set_skill("parry", 180);
   set_skill("martial arts", 50);
   set_skill("perception", 70);
   set_languages(({"common", "stormspeak", "elvish", "yin", "dwarvish",
                "drow", "pix", "treefolk", "vr'krr", "middle-english",
                            "catfolk", "ogryn", "rachk", "gr'grr" }));
   set("storage room",ROOMS+"shop/chest_store");
   set("markup", 20);
   set_property("handedness", "right hand");
   set("no sell", 1);
   ob = new("/d/damned/virtual/great-axe_5.weapon");
   ob->set_property("enchantment", 15);
   ob->set_enh_critical(1);
   ob->move(this_object());
   force_me("wield axe in right hand and left hand");
   ob = new("/d/damned/virtual/studded-leather-vest.armour");
   ob->move(this_object());
   force_me("wear vest");
   ob = new("d/damned/virtual/studded-leather-glove.armour");
   ob->move(this_object());
   force_me("wear glove on right hand");
   ob = new("d/damned/virtual/studded-leather-glove.armour");
   ob->move(this_object());
   force_me("wear glove on left hand");
   ob = new("d/damned/virtual/leather-pants.armour");
   ob->move(this_object());
   force_me("wear pants");
}

int query_num_rounds() { return 3; }

string query_element() { return "vacid"; }
