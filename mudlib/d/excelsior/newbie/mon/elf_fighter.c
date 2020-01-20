// /wizards/excelsior/newbie/mon/elf_fighter.c

inherit "std/monster";

void create() {
	::create();
	set_name("elf");
	set("id",({"warrior elf","warrior","elf scout","fighter elf","elf fighter"}));
	set_level(2);
	set("short","An elf warrior");
	set("long","This is an elf who looks moderately prepared for battle.");
	set("race","high elf");
	set_gender("male");
	set_body_type("human");
	set_overall_ac(3);
	set_class("fighter");
	set_skill("two handed polearm",16);
	set_skill("blade",16);
	set_skill("two handed blade",16);
	set_skill("melee",10);
}
