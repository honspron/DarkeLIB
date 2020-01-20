#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("yrtrid");
	set("id", ({"shopkeeper", "shop keeper", "yrtrid", "kuril mob"}));
	set_level(75);
	set("short", "Yrtrid the Alchemist");
	set("long",
		"Sitting quietly reading a book, he doesn't even look up "
		"to acknowledge your presence in his shop.  But be "
		"assured that someone or something is watching your every "
		"move."
	);
	set_gender("male");
	set_body_type("human");
	set("race", "wraith");
	set_property("melee damage", (["crushing":250]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set_stats("intelligence", 250);
	set_class("arch-mage");
	set("aggressive", 0);
	add_money("silver", random(1000));
	set_languages( ({"common", "yin", "dwarvish"}) );
	set("storage room", ROOMS+"alchemist_storage.c");
	set("no sell", 1);
	set("markup", 40);
}

void catch_tell(string str) {
	string a;

	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_shopper", 1, a);
	}
}

void greet_shopper(string shopper) {
	force_me("speak common");
	force_me("say Greetings!  Welcome to my shop.");
	force_me("bow " + shopper);
}
