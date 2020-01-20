inherit "/std/monster";

void create()
   {
    object ob;
    ::create();
    set_name("monk");
    set("id", ({ "monk", "undead" }));
    set("short", "Undead monk");
    set("long",
        "This tortured and ragged body used to be a " +
         "young monk, even the young ones were powerful.");
    set("aggressive", 1);
    set_level(18);
    set_exp(2000000);
    set_overall_ac(125);
    set_property("enhance criticals",-2);
    set_body_type("human");
    set_alignment(0);
    set("race", "undead");
    set_gender("male");
    set_stats("strength", 150);
    set_stats("dexterity", 75);
    set_stats("constitution", 130);
    set_stats("wisdom", 50);
    set_stats("intelligence", 40);
    set_stats("charisma", 0);
    set_skill("melee", 140);
    set_skill("attack", 170);
    set_skill("dodge", 150);
    set_property("magic resistance", 25);
    set_skill("martial arts",200);
    set_skill("concentrate", 100);
    set_skill("resist stun", 100);
    set_skill("prayer", 140);
    set_spell_level("shields of war", 6);
   add_spell("shields of war","$(ME)");
    set_combat_chance(100);
    set_property("melee damage", ([
         "crushing" : 100 ]) );
   set_max_hp(6000);
   set_max_mp(6000);
   set_hp(6000);
   set_mp(6000);
      }
void init() {
  ::init();
  add_action("block_exit", "east");
  return;
}
