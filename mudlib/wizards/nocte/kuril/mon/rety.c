#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("rety");
	set("id", ({"shopkeeper", "shop keeper", "rety", "kuril mob"}));
	set_level(50);
	set("short", "Rety the Bookbinder");
	set("long",
		"Although only in his twenties, Rety has spent his life "
		"stooped over old tomes learning everything he can. "
		"From the tattoo on his forehead you can see that he is "
		"or once was an apprentice in the School of Necromancy."
	);
	set_gender("male");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":25]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set("aggressive", 0);
	add_money("silver", random(200));
	set_languages( ({"common", "yin", "gerudan", "elvish", "dwarvish"}) );
	set("storage room", ROOMS+"book_binder_storage.c");
	set("no sell", 1);
	set("markup", 20);
}

void catch_tell(string str) {
	string a;
	
	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_shopper", 1, a);
	}
}

void greet_shopper(string shopper) {
	force_me("nod " + shopper +" welcomingly");
}
