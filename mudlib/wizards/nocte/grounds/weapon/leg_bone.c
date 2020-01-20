inherit "/std/weapon";

create() {
	::create();
	set("id", ({ "bone", "leg bone" }) );
	set_name("bone");
	set("short", "bone of some hapless creature");
	set("long",
		"The leg bone of some poor humanoid creature that died to "
		"those gastly creatures."
	);
	set_weight(15);
	set("value", 0);
	set_wc(4, "crushing");
	set_ac(1);
	set_type("blunt");
	set_quality(1);
	set_property("no add quality", 1);
	set_decay_rate(20);
	set_wield("You heft the bone in your hands...doesn't feel too effective.");
	set_unwield("A few flakes of bone drops away from your hands as you loosen your grip on the bone.");
}
