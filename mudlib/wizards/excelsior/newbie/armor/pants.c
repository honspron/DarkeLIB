// /wizards/excelsior/newbie/armor/pants

inherit "std/armour";

void create() {
	::create();
	set_name("pants");
	set("id",({"pants"}));
	set("short","An old pair of pants");
	set("long","These pants look old but still usable.");
	set_type("pants"); 
	set_ac(4);
	set_limbs(({"right leg","left leg"}));
	set_weight(100);
	set_value(50);
}
