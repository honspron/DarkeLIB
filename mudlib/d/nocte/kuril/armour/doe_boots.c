inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id", ({ "boots", "doe skin boots" }) );
	set("short", "doe skin boots");
	set("long",
		"The ultimate in comfort, these soft boots provide the wearer "
		"with comfort and ease in their long travels."
	);
	set_weight(90);
	set_value(65);
	set_type("boots");
	set_limbs( ({"left foot", "right foot"}) );
	set_ac(1);
	set_material("leather");
}
