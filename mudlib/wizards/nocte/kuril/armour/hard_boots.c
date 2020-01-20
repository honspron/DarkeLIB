inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "hard boots" }) );
	set("short", "hard leather boots");
	set("long",
		"Designed with heavy combat in mind, these hard leather boots "
		"offer both durability and some comfort."
	);
	set_weight(100);
	set_value(45);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(2);
	set_material("leather");
}
