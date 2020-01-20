inherit "/std/npc_shop";
 
void create() {
   object ob;
 
   ::create();
   set_name("dai");
   set("id", ({"shopkeeper", "shop keeper", "dai"}));
    add_money("gold", 1000);
   set_level(25);
   set("short","Dai Blackthorn, the shopkeeper");
   set("long",
"Dai is a brooding, slender half-elf.  He sits in the corner, sharpening an "
"impressive-looking dagger.  He acknowledges you by raising an eyebrow.");
   set_gender("male");
   set_body_type("human");
   set("race", "half-elf");
   set_skill("melee", 70);
   set_stats("strength", 500);
   set_overall_ac(40);
   set_skill("dodge", 300);
   set_skill("knife", 300);
   set_skill("perception", 150);
   set_languages(({"common", "pix", "middle-english", "elvish", "drow", "yin", "dwarvish"}));
   set("storage room","/d/damned/guilds/thief/shop_store");
   set("markup", 20);
   set("no sell", 1);
   seteuid(getuid());
   ob = new("/d/damned/virtual/dagger_5.weapon");
   ob->set_property("enchantment", 3);
   ob->add_poisoning(100);
   ob->set_value(2650);
   ob->move(this_object());
   set_property("handedness", "left hand");
   force_me("wield dagger in left hand");
}
 
 
int query_num_rounds() { return 3; }
