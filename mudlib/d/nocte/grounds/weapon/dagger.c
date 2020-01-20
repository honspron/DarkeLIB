inherit "/std/weapon";

create() {
	::create();
	set("id", ({ "dagger" }) );
	set_name("dagger");
	set("short", "small dagger");
	set("long",
		"Quick and deadly...but hardly used."
	);
	set_weight(30);
	set_float_value(0.23);
	set_wc(4, "impaling");
	set_ac(1);
	set_type("knife");
	set_quality(2);
	set_decay_rate(1000);
	set_wield("The grab the small dagger and ready yourself for battle.");
	set_unwield("You sheathe the small dagger.");
}
