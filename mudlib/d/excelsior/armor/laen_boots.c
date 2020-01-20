// /wizards/excelsior/armor/laen_boots

inherit "/std/armour";

void create() {
	::create();
	set_name("boots");
	set("id",({"laen boots","boots","metal boots"}));
	set("short","laen boots");
	set("long","These boots look like they would provide your feet "+
		"unsurpasable protection, as they are made entirely from laen.");
	set_weight(200);
	set_value(23000);
	set_type("boots");
	set_ac(30);
	set_limbs(({ "right foot","left foot" }));
	set_material("/metal/laen");
}
