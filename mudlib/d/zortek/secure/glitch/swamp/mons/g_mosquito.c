//	Wizard:	Glitch
//	Monster: Giant Mosquito
//	File:	g_mosquito.c

#include <std.h>

inherit MONSTER;

create() {
	::create();
	set_name("Giant Mosquito");
	set_id( ({ "mosquito","giant mosquito" }) );
	set_level(6);
	set_short("Giant Mosquito");
	set_long("A very hungry, blood-sucking mosquito");
	set("race", "insect");
	set_gender("female");
	set_body_type("insect");
	set_property("melee damage", ([ "crushing" : 40]));
	set_skill("melee",70);
	set_skill("dodge",45);
	set_skill("parry",45);
	set_skill("attack",70);
	set_stats("dexterity", 90);
	set_stats("intelligence", 20);
	set_stats("strength", 80);
	set_wimpy(5);
	set_alignment(0);
	set_emotes(5, ({
		"The mosquito buzzes angrily.",
		"The mosquito attempts to locate an opening on you back.",
		}),1);
}
