inherit "/std/weapon";

create() {
	::create();
	set("id", ({ "short sword", "sword", "short" }) );
	set_name("sword");
	set("short", "short sword");
	set("long",
		"A weapon of very high quality.  The balance is good and the "
		"blade is made of excellent materials."
	);
	set_weight(45);
	set_wc(7, "cutting");
	set_value(400);
	set_ac(3);
	set_type("blade");
	set_quality(3);
	set_decay_rate(3000);
	set_wield("You brandish the short sword for battle.");
	set_unwield("You feel almost relunctant to remove such a fine weapon.");
}
