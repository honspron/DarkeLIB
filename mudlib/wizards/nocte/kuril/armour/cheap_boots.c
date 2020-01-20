inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "cheap boots" }) );
	set("short", "cheap leather boots");
	set("long",
		"Long worn out, these poor boots have cracks and holes that "
		"allow water and other things to get inside."
	);
	set_weight(120);
	set_value(25);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(1);
	set_material("leather");
}
