// /wizards/excelsior/newbie/weapons/short_sword

inherit "std/weapon";

void create() {
	::create();
	set_name("sword");
	set("id",({"short sword","sword","elven short sword"}));
	set("short","elven short sword");
	set("long","This sword was forged in the ancient ways of the elves.");
	set_ac(3);
	set_wc(9,"cutting");
	set_type("blade");
	set_quality(4);
	set_weight(150);
	set_value(60);
}
