// /wizards/excelsior/newbie/weapons/spear

inherit "std/weapon";

void create() {
	::create();
	set_name("spear");
	set("id",({"spear","a spear","elven spear"}));
	set("short","elven spear");
	set("long","This spear was forged in the ancient ways of the elves.");
	set_ac(2);
	set_wc(10,"impaling");
	set_type("two handed polearm");
	set_quality(3);
	set_weight(140);
	set_value(50);
}
