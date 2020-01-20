// /d/nfd/newbie/monster/teddy_bear

inherit "std/monster";

void reset() {
	::reset();
	set_money("gold",random(10)+1);
}

void create() {
	::create();
	set_name("bear");
	set("id",({"bear","bear cub","cub"}));
	set_level(1);
	set("short","A cute little bear cub");
	set("long","You just feel like hugging this cute little bear.");
	set("race","bear");
	set_gender("neuter");
	set_body_type("human");
	set_overall_ac(2);
	set_skill("attack",6);
	set_skill("dodge",2);
	set_skill("melee",4);
	set_moving(1);
	set_speed(40);
}

