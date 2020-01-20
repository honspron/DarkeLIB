inherit "/std/npc_shop";

void create() {
  object ob;

   ::create();
   set_name("gunther");
   set("id", ({ "gunther", "shopkeeper", "shop keeper" }));
   add_money("gold", 5000);
   set_level(50);
   set_max_hp(200000);
   set_hp(200000);
   set_property("enhance criticals", -60);
   set_exp(3000000);
   set("short","Gunther, the metalsmith");
   set("long",
"Gunther is a stocky dwarf wearing a blacksmith's "
"apron.");
   set_gender("male");
   set_body_type("dwarf");
   set("race", "dwarf");
   set_property("melee damage", ([ "crushing" : 99 ]));
   set_overall_ac(666);
   set_skill("elementalism", 195);
   set_spell_level("elemental storm", 6);
   set_combat_chance(80);
   set_stats("strength", 405);
   set_stats("dexterity", 95);
   set_skill("two handed blade", 190);
   set_skill("dodge", 170);
   set_skill("parry", 180);
   set_skill("martial arts", 170);
   set_skill("perception", 70);
   set_languages(({"common", "stormspeak", "elvish", "yin", "dwarvish",
                "drow", "pix", "treefolk", "vr'krr", "middle-english",
                            "catfolk", "ogryn", "rachk", "gr'grr" }));
   set("storage room","/d/damned/akkad/shops/shop7_store");
   set("markup", 70);
   set_property("handedness", "right hand");
   set("no sell", 0);
   set("pre sell function", (: call_other, this_object(), "only_weapon" :) );
   ob = new("/d/damned/virtual/two-handed-sword_5.weapon");
   ob->set_property("enchantment", 7);
   ob->move(this_object()); 
   ob = new("/d/damned/virtual/studded-leather-vest.armour");
   ob->move(this_object());
   ob = new("d/damned/virtual/studded-leather-glove.armour");
   ob->move(this_object());
   ob = new("d/damned/virtual/studded-leather-glove.armour");
   ob->move(this_object());
   ob = new("d/damned/virtual/leather-pants.armour");
   ob->move(this_object());
   force_me("wield sword in right hand and left hand");
   force_me("wear vest");
   force_me("wear glove on right hand");
   force_me("wear glove 2 on left hand");
   force_me("wear pants");
   return;
}

string only_weapon(object item) {
  if(!item->is_weapon()) return "I only buy weapons.";
  return 0;
}


int query_num_rounds() { return 6; }

string query_element() { return "vacid"; }
