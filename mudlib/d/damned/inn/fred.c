
inherit "/std/npc_shop";
object monster;


void reset() {
   ::reset();
   monster = this_object();
   monster->set_money("gold", 1000);
   monster->move(this_object());
}

void create() {
   ::create();
   set_name("fred");
   set("id", ({"shopkeeper", "shop keeper", "fred"}));
   set_level(12);
   set_exp(370000);
   set("short","Fred Bodett, the shopkeeper");
   set("long","Fred is Toms brother and runs the gift shop of The Blue Dragon "+
      " Fred is very strong and not one to mess with.");
   set_gender("male");
   set_body_type("human");
   this_object()->set_race("high-man");
   set_skill("melee", 70);
   set_skill("dodge", 70);
   set_skill("perception", 95);
   set_overall_ac( 5 );
   set_languages(({"common", "elvish", "serra", "yin", "dwarvish"}));
   set("storage room","/d/damned/inn/gift_shop_store");
   set("markup", 75);
}
