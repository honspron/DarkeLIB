// /d/nfd/newbie/weapons/spiked_long_sword

inherit "std/weapon";

void create() {
	::create();
	set_name("sword");
	set("id",({"long sword","sword","elven long sword","spiked long sword"}));
	set("short","nasty looking long sword");
	set("long","This sword was forged in the ancient ways of the elves. On the "+
		"back side are large menacing looking spikes used to inflict more damage.");
	set_ac(3);
	set_wc(10,"impaling");
	set_type("two handed blade");
	set_quality(4);
	set_weight(130);
	set_value(75);
}
