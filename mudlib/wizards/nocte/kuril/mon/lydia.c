#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("lydia");
	set("id", ({"shopkeeper", "shop keeper", "lydia", "kuril mob"}));
	set_level(50);
	set("short", "Lydia the Candlemaker");
	set("long",
		"Red hair as fiery as the candles that burn in her shop, "
		"Lydia, gives you the once over as you enter her small "
		"shop."
	);
	set_gender("female");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":25]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set("aggressive", 0);
	add_money("silver", random(200));
	set_languages( ({"common", "dwarvish"}) );
	set("storage room", ROOMS+"candle_shop_storage.c");
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
	force_me("say Oh, why hello there.  Welcome to my small shop.");
	force_me("smile");
}
