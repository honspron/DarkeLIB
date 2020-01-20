// /wizards/excelsior/weapons/battle_axe.c

inherit "/std/weapon";

void create() {
	::create();
	set_name("axe");
	set("id",({"axe","battle axe"}));
	set("short","A large battle axe");
	set("long","This is a large battle axe good for hitting things with.");
	set_weight(300);
	set_value(600);
	set_ac(1);
	set_wc(11,"cutting");
	set_type("axe");
	set_quality(4);
}
