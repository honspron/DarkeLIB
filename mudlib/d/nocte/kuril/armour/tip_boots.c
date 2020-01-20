inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "metal tipped boots" }) );
	set("short", "metal tipped boots");
	set("long",
		"With the added protection of small metal plates, these "
		"boots give both added protection and ease of mobility."
	);
	set_weight(120);
	set_value(85);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(5);
	set_material("leather");
}
