#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	::create();
	set_name("tendra");
	set("id", ({"shopkeeper", "shop keeper", "tendra", "kuril mob"}));
	set_level(75);
	set("short", "Tendra the Sorceress");
	set("long",
		"Moving her seductive body around the counter, she allows "
		"her night black hair to fall over her pale shoulders.  "
		"She whispers to you: 'May I help you?'"
	);
	set_gender("female");
	set_body_type("human");
	set("race", "high-man");
	set_property("melee damage", (["crushing":250]));
	set_overall_ac(100);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set_stats("intelligence", 250);
	set_class("arch-mage");
	set("aggressive", 0);
	add_money("silver", random(3000));
	set_languages( ({"common", "yin", "dwarvish"}) );
	set("storage room", ROOMS+"magic_shop_storage.c");
	set("no sell", 1);
	set("markup", 50);
}

void catch_tell(string str) {
	string a;

	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_shopper", 1, a);
	}
}

void greet_shopper(string shopper) {
	force_me("speak common");
	force_me("say Greetings to you.  Welcome to my magic shop.  "
		"I specialize in permanent magical pets.  Just 'shatter' "
		"an orb on the ground and a permanent loyal pet will emerge "
		"to serve you.");
}
