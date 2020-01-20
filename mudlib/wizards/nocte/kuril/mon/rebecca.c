#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("rebecca");
	set("id", ({"shopkeeper", "shop keeper", "rebecca", "kuril mob"}));
	set_level(50);
	set("short", "Rebecca the Baker");
	set("long",
		"From her full figure it is obvious that Rebecca truly "
		"enjoys her work.  Bright eyes contrast the dark "
		"surroundings of the city."
	);
	set_gender("female");
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
	set("storage room", ROOMS+"bakery_storage.c");
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
	force_me("say Please let me know if there is anything you need.");
	message("info", "Rebecca quickly continues with her work.  Putting "
		"another sheet of cookies into a brick oven.", ENV(TO),
		({TO}) );
}

