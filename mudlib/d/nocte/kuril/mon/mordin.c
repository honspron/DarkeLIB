#include "nevin.h"
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("mordin");
	set("id", ({"shopkeeper", "shop keeper", "mordin", "kuril mob"}));
	set_level(50);
	set("short", "Mordin the Enbalmer");
	set("long",
		"Howdy"
	);
	set_gender("male");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":150]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set("aggressive", 0);
	add_money("silver", 1000);
	set_languages( ({"common", "yin"}) );
	set("storage room", ROOMS+"corpse_market_storage.c");
	set("no sell", 1);
	set("markup", 30);
}

void catch_tell(string str) {
	string a;

	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_shopper", 1, a);
	}
}

void greet_shopper(string shopper) {
	force_me("speak common");
	force_me("say Good evening to you.  My you find a suitable receptacle "
		"for your skills here in my shop.");
	force_me("grin");
}
