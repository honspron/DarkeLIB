// /d/nfd/armor/iron_boots



inherit "/std/armour";



void create() {

	::create();

	set_name("boots");

	set("id",({"iron boots","boots","metal boots"}));

	set("short","iron boots");

	set("long","These boots look like they would provide your feet "+

		"excellent protection, as they are made entirely from iron.");

	set_weight(200);

	set_value(5000);

	set_type("boots");

	set_ac(15);

	set_limbs(({ "right foot","left foot" }));

}

