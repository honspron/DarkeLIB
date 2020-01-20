inherit "/std/armour";

void create() {
	::create();
	set_name("supple leather gloves");
	set("id", ({ "gloves", "leather gloves", "supple gloves",
		"supple leather gloves"}) );
	set("short", "supple leather gloves");
	set("long", "Soft and warm for those cold nights.");
	set_weight(30);
	set_value(50);
	set_type("glove");
	set_limbs( ({ "right hand", "left hand", "first hand", "second hand",
		"third hand", "fourth hand" }) );
	set_ac(3);
	set_material("leather");
}
