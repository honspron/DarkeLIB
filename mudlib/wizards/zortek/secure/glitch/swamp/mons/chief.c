//	Wizard:  Glitch
//	Monster: Chief Troll
//	File:	chief.c

#include <std.h>

inherit MONSTER;

create() {
	object money;
	::create();
	set_name("Chief Troll");
	set_id( ({ "chief","chief troll" }) );
	set_level(17);
	set_short("Chief Troll");
	set_long("The biggest and nastiest troll you have seen.");
	set("race", "troll");
	set_gender("male");
	set_body_type("troll");
	set_wielding_limbs( ({ "right hand", "left hand" }) );
	set_property("melee damage", ([ "crushing" : 90]));
	set_skill("melee", 90);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_skill("attack", 90);
	set_skill("two handed", 90);
	set_stats("dexterity", 85);
	set_stats("intelligence", 50);
	set_stats("strength", 125);
	set_wimpy(0);
	new("/d/damned/virtual/two-handed-sword_5.weapon")->move(this_object());
	force_me("wield sword in right hand and left hand");
	new("/d/damned/virtual/breast-plate.armour")->move(this_object());
	force_me("wear plate");
	new("/d/damned/virtual/iron-greaves.armour")->move(this_object());
	force_me("wear greaves");
	money=new("std/obj/coins");
	money->set_money("gold",(random(50)+500));
	money->move(this_object());
	set_emotes(5, ({
		"The chief grins at your.",
		"The chief laughs at your minor attempts.",
		"The chief growls loudly.",
		"The chief swings a round-house at you.",
		"The chief attempts to bash your skill.",
		}),1);
}
