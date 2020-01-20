inherit "/std/monster";

void create() {
   object ob;
   ::create();
   set_name("snowman");
   set("id", ({ "snowman" }));
   set("short", "a snowman");
   set("long", "This is a snowman guard that is magically formed "
	"by ice and snow. It guards the entrance to the Ash caves. "
	"It is said there is a treasure hidden in the caves that is "
	"far greater than any money or gold. One of the snowmen "
	"guards the entrance to the caves while the others don't. "
	"Be wary if you try to find the treasure.");
   set("aggressive", 1);
   set_level(7);
   set_body_type("human");
   set_alignment(-100);
   set("race", "elemental");
   set_stats("strength", 90);
   set_stats("dexterity", 75);
   set_overall_ac(8);
   set_exp(60000);
   set_max_hp(700);
   set_max_mp(700);
   set_skill("attack", 60);
   set_skill("defense", 30);
   set_skill("parry", 30);
   set_skill("melee", 50);
   set_skill("blade", 70);
   set_skill("conjuration", 70);
   set_skill("concentrate", 90);
   set("concentrate", 1);
   set_spell_level("ice dagger", 4);
   set_combat_chance(80);
   add_spell("ice_dagger", "$A");
   set_languages( ({"common"}) );
   set_speech(10, "common", ({"One of us guards the gateway. "
	"The others guard near certain death. The treasure awaits."}),0);
   ob = new("wizards/mushroom/obj/weapons/ice_sword");
   ob->move(this_object());
   force_me("wield sword in right hand");
   return;
}
