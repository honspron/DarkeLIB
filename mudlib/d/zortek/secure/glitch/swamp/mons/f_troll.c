//	Wizard:	Glitch
//	Monster: Troll female
//	File:	f_troll.c

#include <std.h>

inherit MONSTER;

create() {
	object money;
	::create();
		set_name("Troll");
		set_id( ({ "troll","female troll" }) );
		set_level(11);
		set_short("Troll");
		set_long("This huge female troll looks like she can rip your "+
			"head off and looks like she wants to.");
		set("race","troll");
		set_gender("female");
		set_body_type("troll");
		set_wielding_limbs( ({ "right hand", "left hand" }) );
		set_property("melee damage", ([ "crushing" : 70]));
		set_skill("melee", 70);
		set_skill("dodge", 70);
		set_skill("parry", 70);
		set_skill("attack", 70);
		set_skill("two handed polearm", 80);
		set_stats("dexterity", 90);
		set_stats("intelligence", 50);
		set_stats("strength", 103);
		set_wimpy(3);
		set_alignment(-100);
		new("/d/damned/virtual/glaive_5.weapon")->move(this_object());
		force_me("wield glaive on left hand and right hand");
		new("/d/damned/virtual/breast-plate.armour")->move(this_object());
		force_me("wear plate");
		money=new("std/obj/coins");
		money->set_money("gold",(random(40)+30));
		money->move(this_object());
		set_emotes(5, ({
			"The troll growls at you.",
			"The troll roars in triumph as he slashes at you.",
			}),1);
}
