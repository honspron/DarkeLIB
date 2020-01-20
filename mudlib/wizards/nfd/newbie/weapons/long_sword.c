// /d/nfd/newbie/weapons/long_sword

inherit "std/weapon";

void create() {
	::create();
	set_name("sword");
	set("id",({"long sword","sword","elven long sword"}));
	set("short","elven long sword");
	set("long","This sword was forged in the ancient ways of the elves.");
	set_ac(2);
	set_wc(9,"cutting");
	set_type("two handed blade");
	set_quality(4);
	set_weight(190);
	set_value(69);
	set_material("/metal/steel");
}
