#include <std.h>
#include <nevin.h>
inherit "/std/npc_shop";

void create() {
	object ob;
	::create();
	set_name("lupo");
	set("id", ({"shopkeeper", "shop keeper", "lupo", "kuril mob"}));
	set_level(50);
	set("short", "Lupo the Butcher");
	set("long",
		"Obviously infuriated at his work, he stomps about the " +
		"room kicking pieces of meat around.  You better hope he " +
		" doesn't decide to swing that cleaver at you!"
	);
	set_gender("male");
	set_body_type("human");
	set("race", "human");
	set_property("melee damage", (["crushing":75]));
	set_overall_ac(30);
	set_max_hp(10000000);
	set_hp(10000000);
	set_exp(1000000);
	set_class("fighter");
	set("aggressive", 0);
	add_money("silver", 200 + random(500));
	set_languages( ({"common", "yin", "dwarvish"}) );
	set("storage room", ROOMS+"butcher_shop_storage.c");
	set_emotes(5, ({"Lupo starts kicking a dirty of piece of meat around the room.", "Lupo takes a mighty swing with his cleaver--only to take off his own thumb!", "Lupo runs around the room screaming in pain."}), 0);
	set_achats(5, ({"Lupo the Butcher screams: I KIILLLL YOUUUUU!!!"}) );
	set("no sell", 1);
	set("markup", 20);
	new(WEAP+"cleaver")->move(TO);
	force_me("wield cleaver in right hand");
}
