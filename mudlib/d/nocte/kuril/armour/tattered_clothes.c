inherit "/std/armour";

void create() {
	::create();
	set_name("tattered clothes");
	set("id", ({"clothes", "tattered clothes"}) );
	set("short", "tattered clothes");
	set("long",
		"A disgusting collection of assorted clothes."
	);
	set_type("armor");
	set_ac(1);
	set_limbs( ({ "torso", "left arm", "right arm", "left leg",
		"right leg" }) );
	set_value(0);
	set_weight(100);
	set_material("leather");
}
