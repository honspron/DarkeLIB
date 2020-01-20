#include "nevin.h"
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("dnerr");
	set("id", ({"shopkeeper", "shop keeper", "dnerr", "kuril mob"}));
	set_level(50);
	set("short", "Dnerr the Shopkeeper");
	set("long",
		""
	);
	set_gender("male");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":100]));
	set_overall_ac(30);
	set_skill("attack", 200);
	set_skill("parry", 200);
	set_skill("block", 200);
	set_skill("melee", 200);
	set_skill("dodge", 200);
	set_skill("knife", 200);
	set_skill("perception", 200);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set_stats("strength", 250);
	set_class("tinker");
	set("aggressive", 0);
	add_money("gold", 2000);
	set_languages( ({"common", "yin", "dwarvish"}) );
	set("storage room", ROOMS+"general_store_storage.c");
	set("no sell", 1);
	set("markup", 30);
}

void catch_tell(string str) {
	string a, lang;
	
	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_shopper", 1, a);
	}
}

void greet_shopper(string shopper) {
	force_me("speak common");
	force_me("say Welcome to my humble shop.  May you find something that "
		"suits you today.");
	force_me("smile " + shopper);
}

