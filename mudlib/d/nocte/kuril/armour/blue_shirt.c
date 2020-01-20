inherit "/std/armour";

void create() {
	::create();
	set_name("shirt");
	set("id", ({ "shirt", "blue shirt", "light blue shirt" }) );
	set("short", "light blue shirt");
	set("long",
		"Light blue, just the ocean upon which the sailors that "
		"where them sail upon."
	);
	set_type("body armour");
	set_ac(2);
	set_weight(50);
	set_value(20);
	set_material("cloth");
}
