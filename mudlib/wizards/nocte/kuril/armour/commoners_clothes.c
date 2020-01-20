inherit "/std/armour";

void create() {
	::create();
	set_name("commoners clothes");
	set("id", ({"clothes", "commoners clothes"}) );
	set("short", "commoners' clothes");
	set("long",
		"A set of common clothes worn by the citizens of Kuril."
	);
	set_type("armor");
	set_ac(5);
	set_limbs( ({ "torso", "left arm", "right arm", "left leg",
		"right leg" }) );
	set_value(50);
	set_weight(150);
	set_material("cloth");
}
