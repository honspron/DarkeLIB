inherit "/std/npc_shop";

void create() {
   ::create();
   set_name("simon");
   set("id", ({"shopkeeper", "shop keeper", "simon"}));
    add_money("gold", 45);
   set_level(14);
   set("short","Simon, the shopkeeper");
   set("long","Simon is an elderly high-man, he looks as if he has seen
much of the world. Now retired form advanturing he works as the shopkeeper
for a small store in the Rangers' guild.");
   set_gender("male");
   set_body_type("human");
   set("race", "high-man");
   set_property("melee damage", ([ "crushing" : 65 ]));
   set_overall_ac(40);
   set_skill("melee", 125);
   set_max_hp(1200);
   set_hp(1200);
   set_skill("dodge", 70);
   set_skill("perception", 95);
   set_skill("parry", 120);
   set_languages(({"common", "stormspeak", "elvish", "serra", "yin",
"dwarvish", "drow", "middle-english", "mountainspeak" }));
   set("storage room","/d/damned/guilds/ranger/shop_store");
   set("markup", 40);
}
