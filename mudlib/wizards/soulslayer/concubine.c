inherit "/std/monster";

void create() {
   object ob;
   ::create();
   set_name("concubine mariah");
   set("id", ({ "concubine", "mariah" }));
   set("short", "Mariah, Concubine of Lord Soulslayer");
   set("long",
	"Her desc goes here.");
   set_level(20);
   set("race", "demon");
   set_body_type("winged-humanoid");
   set_exp(350000);
   add_money("gold", 0);
   set_max_hp(25000);
   set_max_mp(25000);
   set_hp(25000);
   set_mp(25000);
   set_overall_ac(10);
   set_alignment(-1000);
   set_stats("strength", 185);
   set_stats("constitution", 170);
   set_stats("dexterity", 120);
   set_stats("charisma", 180);
   set_stats("intelligence", 150);
   set_stats("wisdom", 150);
   set_skill("melee", 190);
   set_skill("attack", 190);
   set_skill("blade", 150);
   set_skill("defense", 120);
   set_skill("parry", 140);
   
   // important or cant understand talk! SS
   set_languages("common");
   set_lang_prof("common", 10);
   return;
}

void init() {
    ::init();
//    if( strcmp(this_player()->query_name(), "soulslayer") == 0 )
//      tell_room(environment(this_object()), "Mariah says in elvish: Greetings m'lord, may I be of service to you?", ({this_object()}));
}
