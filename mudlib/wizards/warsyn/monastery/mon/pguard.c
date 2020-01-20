inherit "/std/monster";
void create()
   {
    object ob;
    ::create();
    set_name("guard");
    set("id", ({ "paladin", "guard" }));
    set("short", "Paladin guard");
    set("long",
        "This holy warrior looks powerful and very rooted " +
         " in place.  He seems very serious about his position");
    set("aggressive", 0);
    set_level(18);
    set_exp(3000000);
    set_overall_ac(125);
    set_property("enhance criticals",-2);
    set_body_type("human");
    set_alignment(0);
    set("race", "high-man");
    set_gender("male");
    set_stats("strength", 115);
    set_stats("dexterity", 100);
    set_stats("constitution", 100);
    set_stats("wisdom", 110);
    set_stats("intelligence", 100);
    set_stats("charisma", 100);
    set_skill("melee", 140);
    set_skill("attack", 120);
    set_skill("dodge", 150);
    set_property("magic resistance", 15);
    set_skill("martial_arts", 10);
    set_skill("prayer",200);
    set_skill("blade",130);
    set_skill("concentrate", 100);
    set_skill("perception",110);
    set_skill("resist stun", 100);
    set_spell_level("divine punishment", 6);
    add_spell("divine punishment","$A");
    set_combat_chance(100);
    set_property("melee damage", ([
        "crushing" : 20,
                              ]) );
   set_max_hp(6000);
   set_max_mp(6000);
   set_hp(6000);
   set_mp(6000);
   set_property("handedness", "right hand");
   new("/wizards/warsyn/monastery/weapons/defender.c")->
          move(this_object());
   new("/wizards/warsyn/monastery/armour/field-plate.c")->
          move(this_object());
   force_me("wear armor");
   force_me("wield defender in right hand and left hand");
}

