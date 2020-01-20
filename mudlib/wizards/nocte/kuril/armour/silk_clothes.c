inherit "/std/armour";

void create() {
	::create();
	set_name("silk clothes");
	set("id", ({"clothes", "silk clothes"}) );
	set("short", "silk clothes");
	set("long",
		"Such fashionable clothes!  These clothes must be very "
		"expensive, for they are very soft and comfortable to wear."
	);
	set_type("armor");
	set_ac(8);
	set_limbs( ({ "torso", "left arm", "right arm", "left leg",
		"right leg" }) );
	set_value(200);
	set_weight(100);
	set_material("silk");
}
