#include "nevin.h"
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("llendov");
	set("id", ({"shopkeeper", "shop keeper", "llendov", "kuril mob"}));
	set_level(50);
	set("short", "Llendov the Limner");
	set("long",
		""
	);
	set_gender("male");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":25]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set("aggressive", 0);
	add_money("silver", 200);
	set_languages( ({"common", "dwarvish"}) );
	set("storage room", ROOMS+"parchment_shop_storage.c");
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
	force_me("speak common");
	force_me("say Greetings traveller.  Please feel free to examine my "
		"wares.");
	force_me("bow " + shopper);
}
