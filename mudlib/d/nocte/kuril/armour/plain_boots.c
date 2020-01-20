inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "plain boots" }) );
	set("short", "plain leather boots");
	set("long",
		"A pair of leather boots, nothing fancy, nothing spectacular."
	);
	set_weight(80);
	set_value(25);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(1);
	set_material("leather");
}
