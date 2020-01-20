//	Wizard:	Glitch
//	Monster: Ranger
//	File:	ranger.c

#include <std.h>

inherit MONSTER;

create() {
	object money;
	::create();
		set_name("Ranger");
		set_id( ({ "ranger" }) );
		set_level(8);
		set_short("Ranger");
		set_long("The ranger patrols here to keep creatures from exiting the swamp.");
		set("race", "wood-elf");
		set_gender("male");
		set_body_type("human");
		set_wielding_limbs( ({ "right hand", "left hand" }) );
		set_property("melee damage", ([ "slashing" : 60]));
		set_skill("melee", 58);
		set_skill("dodge", 58);
		set_skill("parry", 58);
		set_skill("attack", 58);
		set_skill("blade", 66);
		set_stats("dexterity", 78);
		set_stats("intelligence", 95);
		set_stats("strength", 100);
		set_wimpy(0);
		set_alignment(250);
		new("/d/damned/virtual/two-handed-sword_5.weapon")->move(this_object());
		force_me("wield sword in left hand and right hand");
		new("/d/damned/virtual/breast-plate.armour")->move(this_object());
		force_me("wear breast plate");
		new("/d/damned/virtual/great-helm.armour")->move(this_object());
		force_me("wear helm");
		money=new("std/obj/coins");
		money->set_money("gold",(random(30)+60));
		money->move(this_object());
}

