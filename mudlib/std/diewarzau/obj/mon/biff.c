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

   set("id", ({"shopkeeper", "shop keeper", "biff"}));

   set_level(18);

   set("short","Biff, the shopkeeper");

   set("long",

"Biff is a big gentleman who looks like he wants to sell you some stuff.");

   set_gender("male");

      set_body_type("human");

   this_object()->set_race("high-man");

  set_property("melee damage", ([ "crushing" : 30]));

   set_skill("melee", 70);

   set_skill("dodge", 70);

   set_skill("parry", 100);

   set_skill("perception", 95);

   set_overall_ac( 10 );

   set_languages(({"common", "elvish", "serra", "yin", "dwarvish"}));

   set("storage room","/wizards/diewarzau/rooms/weapon_store");

   set("markup", 50);

}

