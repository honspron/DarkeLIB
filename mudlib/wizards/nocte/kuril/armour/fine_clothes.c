inherit "/std/armour";

void create() {
	::create();
	set_name("fine clothes");
	set("id", ({"clothes", "fine clothes"}) );
	set("short", "fine clothes");
	set("long",
		"An expensive set of clothes to wear." 
	);
	set_type("armor");
	set_ac(5);
	set_limbs( ({ "torso", "left arm", "right arm", "left leg",
		"right leg" }) );
	set_value(300);
	set_weight(300);
	set_material("silk");
}
