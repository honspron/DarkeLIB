inherit "/std/armour";

void create() {
	::create();
	set_name("shirt");
	set("id", ({ "shirt", "dirty shirt" }) );
	set("short", "dirty shirt");
	set("long",
		"Smelly and foul from days, and perhaps weeks of wear, "
		"this shirt smells just like its owner--yuck!"
	);
	set_type("body armour");
	set_ac(2);
	set_weight(50);
	set_value(20);
	set_material("cloth");
}
