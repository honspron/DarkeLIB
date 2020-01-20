#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("kerchesh");
	set("id", ({"shopkeeper", "shop keeper", "kerchesh", "kuril mob"}));
	set_level(50);
	set("short", "Kerchesh the Fish Seller");
	set("long",
		"A smelly little man, Kerchesh makes his living selling "
		"fish near the docks of Kuril."
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
	add_money("silver", random(200));
	set_languages( ({"common"}) );
	set("storage room", ROOMS+"fish_market_storage");
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
	force_me("yell Fresh Fish!  Fresh fish for sale!");
}
