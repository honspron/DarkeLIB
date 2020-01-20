inherit "/std/monster";
void create() {
   ::create();
    set_name("volunteer");
    set("id", ({"volunteer", "ntf volunteer", "kitchen helper"}));
    add_money("silver", 5);
    set_level(30);
    set_exp(5000);
    set_max_hp(10000000);
    set_hp(10000000);
    set_property("enhance criticals", -10);
    set_property("melee damage", ([ "crushing" : 99]));
    set("short", "NTF Volunteer");
    set("long",
    "The NTF is manned by many volunteers throughout the realms "
    "and has setup shop here to help the less fortunate thieves of Daybreak Ridge.");
    set_gender("female");
    set_body_type("human");
    set("race", "halfling");
    set_skill("conjuration", 170);
    set_skill("elementalism", 175);
    set_spell_level("elemental storm", 6);
    add_spell("elemental storm", "");
    set_combat_chance(150);
    set_skill("dodge", 80);
    set_skill("parry", 80);
    set_skill("martial arts", 200);
    set_skill("perception", 95);
    set_languages(({"common", "stormspeak", "elvish", "serra", "yin", "dwarvish",
                "drow", "pix", "treefolk", "vr'krr", "middle-english",
		"catfolk","undead-tongue", "hisaaa", "ogryn" }));
    set_stats("dexterity", 150);
    set_stats("strength", 200);
    set("num rounds", 2);
    set_emotes(5, ({
"Volunteer says, \"Hello!  Welcome, welcome one and all!\"",
"Volunteer says, \"Please won't you join us. There's plenty for everyone!\"",
"Volunteer sings, \"We are the NTF...  we are proudly serving out some soup...  we help those who can't steal for themselves by offering them some hot goop.\"",
}),0);

}
string query_element() { return "vacid"; }
