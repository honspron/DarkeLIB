// /wizards/excelsior/armor/lab_coat
// sorry armor, don't use it

inherit "std/armour";

void create() {
	::create();
	set_name("coat");
	set("id",({"coat","lab coat"}) );
	set("short","A lab coat");
	set("long","A clean coat for doctors to wear.");
	set_type("body amour");
	set_ac(1);
	set_limbs( ({"right arm","left arm"}) );
	set_weight(36);
	set_value(20);
}
