inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("bruno");
   set("id", ({"shopkeeper", "shop keeper", "bruno"}));
   set_level(12);
   set("short","Bruno, the shopkeeper");
   set("long",
"Bruno is an imposing dwarf whom you swear is as wide as "
"he is tall.  He wears a leather blacksmith's apron, and "
"tufts of grey hair protrude from his chest. You'd laugh at him if "+
"you weren't so scared that he'd beat you to a bloody pulp.");
   set_gender("male");
   set_body_type("human");
   set("race", "dwarf");
  set_property("melee damage", ([ "crushing" : 45]));
  set_overall_ac(30);
  set_skill("melee", 80);
  set_stats("strength", 130);
  set_max_hp(1000);
  set_hp(1000);
  set_skill("dodge", 70);
   set_skill("perception", 80);
   set_languages(({"stormspeak", "mountainspeak", "common", "elvish", "treefolk", "serra", "yin", "dwarvish"}));
   set("storage room","/d/damned/guilds/tinker/shop_store");
   set("pre sell function", (: call_other, this_object(), "sell_ingot" :) );
   set("markup", 20);
}

string sell_ingot(object what) {
  if(!what->id("ingot"))
    return "You may only sell ingots here.";
  return 0;
}
