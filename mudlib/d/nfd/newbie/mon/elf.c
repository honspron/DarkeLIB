// /d/nfd/newbie/mon/elf.c

inherit "std/monster";

void create() {
	::create();
	set_name("elf");
	set("id",({"common elf","elf"}));
	set_level(1);
	set("short","A common elf minding his own business");
	set("long","This is an elf just minding his own business.");
	set("race","high elf");
	set_gender("male");
	set_body_type("human");
	set_overall_ac(3);
	set_skill("two handed polearm",13);
	set_skill("blade",9);
	set_skill("two handed blade",11);
	set_skill("melee",8);
}
