inherit "/std/armour";

void create() {
	::create();
	set_name("pants");
	set("id", ({ "pants", "soiled pants"}) );
	set("short", "soiled pants");
	set("long",
		"Filthy filthy filthy!  How could anyone stand to wear these "
		"things.  You just cringe at the though of putting them on."
	);
	set_weight(70);
	set_type("pants");
	set_value(5);
	set_limbs( ({"right leg", "left leg" }) );
	set_ac(2);
	set_material("cloth");
}
