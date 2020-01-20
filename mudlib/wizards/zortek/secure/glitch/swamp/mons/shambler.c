//	Wizard:	Glitch
//	Monster: Shambling Mound
//	file:	shambler.c

#include <std.h>

inherit MONSTER;

create() {
	object money;
	::create();
		set_name("Shambling Mound");
		set_id( ({ "mound","shambling mound","shambler" }) );
		set_level(12);
		set_short("Shambling Mound");
		set_long("A mass of vegetation rises from the swamp to "+
			"confront you.");
		set("race", "plant");
		set_gender("male");
		set_body_type("human");
		set_wielding_limbs( ({ "right hand","left hand" }) );
		set_property("melee damage", ([ "crushing" : 100]));
		set_skill("melee", 100);
		set_skill("dodge", 85);
		set_skill("parry", 85);
		set_skill("attack", 100);
		set_stats("strength",100);
		set_wimpy(0);
		set_alignment(0);
		money=new("std/obj/coins");
		money->set_money("gold",(random(80)+50));
		money->move(this_object());
		set_emotes(5, ({
			"The Shambling Mound moans.",
			"The Shambling Mound oozes towards you.",
			"The Shambling mound sprays water over you.",
		}),1);
}
