// /d/nfd/newbie/mon/elf.c

inherit "std/monster";

void create() {
	::create();
	set_name("elf child");
	set("id",({"child","elf"}));
	set_level(1);
	set("short","A small elf child who looks alone and afraid");
	set("long","This is an elf child who looks lonely and afraid.  He stares up at you with trembling eyes.");
	set("race","high elf");
	set_gender("male");
	set_body_type("human");
	set_overall_ac(1);
}
