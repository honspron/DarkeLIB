//	Wizard:	Glitch
//	Monster: Giant Crocodile
//	File:	g_croc.c

#include <std.h>

inherit MONSTER;

create() {
	::create();
	set_name("Giant Crocodile");
	set_id( ({ "crocodile","giant crocodile" }) );
	set_level(10);
	set_short("Giant Crocodile");
	set_long("A giant crocodile glares at you.");
	set("race","reptile");
	set_gender("female");
	set_body_type("reptile");
	set_property("melee damage", ([ "biting" : 90]));
	set_skill("melee", 90);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_stats("strength", 90);
	set_wimpy(5);
	set_alignment(0);
	set_emotes(5, ({
		"The crocodile growls at you.",
		"The crocodile slides a little closer to you.",
		"The crocodile bares it's teeth at you.",
		}),1);
}
