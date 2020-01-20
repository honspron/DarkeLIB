// /d/nfd/newbie/armor/sweater

inherit "std/armour";

void create() {
	::create();
	set_name("sweater");
	set_id(({"sweater","a sweater"}));
	set("short","A dirty sweater");
	set_long("This is a dirty sweater that looks like it would provide "+
		"minimal protection to the wearer.");
	set_type("sweater");
	set_ac(4);
	set_limbs(({"torso"}));
	set_weight(95);
	set_value(15);
	set_material("/misc/cotton");
}
