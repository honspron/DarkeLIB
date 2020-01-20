//	Wizard:	Glitch
//	Monster: Troll Warrior
//	File:	w_troll.c

#include <std.h>

inherit MONSTER;

create() {
	object money;
	::create();
		set_name("Troll");
		set_id( ({ "troll","troll warrior" }) );
		set_level(13);
		set_short("Troll");
		set_long("This huge troll looks like he is ready to deal with "+
			"interlopers like you.");
		set("race","troll");
		set_gender("male");
		set_body_type("troll");
		set_wielding_limbs( ({ "right hand", "left hand" }) );
		set_property("melee damage", ([ "crushing" : 75]));
		set_skill("melee", 73);
		set_skill("dodge", 73);
		set_skill("parry", 71);
		set_skill("attack", 72);
		set_skill("two handed polearm", 83);
		set_stats("dexterity", 90);
		set_stats("intelligence", 50);
		set_stats("strength", 103);
		set_wimpy(3);
		set_alignment(-100);
		new("/d/damned/virtual/glaive_5.weapon")->move(this_object());
		force_me("wield glaive on left hand and right hand");
		new("/d/damned/virtual/breast-plate.armour")->move(this_object());
		force_me("wear plate");
		new("/d/damned/virtual/great-helm.armour")->move(this_object());
		force_me("wear helm");
		new("/d/damned/virtual/iron-bracer.armour")->move(this_object());
		force_me("wear bracer on right arm");
		new("/d/damned/virtual/iron-bracer.armour")->move(this_object());
		force_me("wear bracer 2 on left arm");
		money=new("std/obj/coins");
		money->set_money("gold",(random(40)+30));
		money->move(this_object());
		set_emotes(5, ({
			"The troll growls at you.",
			"The troll roars in triumph as he slashes at you.",
			}),1);
}
