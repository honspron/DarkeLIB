inherit "/std/armour";

void create() {
	::create();
	set_name("leather girdle");
	set("id", ({"belt", "girdle", "leather girdle"}) );
	set("short", "leather girdle");
	set("long",
		"A thick leather belt."
	);
	set_weight(90);
	set_value(50);
	set_type("belt");
	set_ac(7);
	return;
	set_material("leather");
}
