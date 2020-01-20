inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "high boots" }) );
	set("short", "high leather boots");
	set("long",
		"For the seafarer, these high boots help the wearer by "
		"providing the necessary ankle support on those rocking "
		"ship decks."
	);
	set_weight(120);
	set_value(95);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(2);
	set_material("leather");
}
