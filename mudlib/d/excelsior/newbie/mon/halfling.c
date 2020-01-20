 // /wizards/excelsior/newbie/mon/halfling.c

inherit "std/monster";

void create() {
	::create();
	set_name("elf");
	set("id",({"halfling","halfling child","young halfling","a halfling"}));
	set_level(1);
	set("short","A young halfling");
	set("long","This is a young halfling who looks very innocent and nice.");
	set("race","halfling");
	set_skill("dodge",0);
		set_skill("parry",0);
		set_skill("attack",4);
		set_skill("melee",5);
	set_gender("male");
	set_body_type("human");
	set_overall_ac(3);
	set_class("child");
	set_exp(200);
}
