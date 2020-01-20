#include "nevin.h"
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("abeyaratne");
	set("id", ({"shopkeeper", "shop keeper", "abeyaratne"}));
	set_level(50);
	set("short", "Abeyaratne the corpse buyer");
	set("long",
		"Wearing grime covered clothes, he asks if you have a corpse "
		"that you would like to sell to him."
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
	add_money("gold", 1000);
	set_languages( ({"common", "yin"}) );
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
	force_me("nod");
}
