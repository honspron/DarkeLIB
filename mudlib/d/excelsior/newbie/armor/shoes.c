// /wizards/excelsior/newbie/armor/shoes

inherit "std/armour";

void create() {
	::create();
	set_name("shoes");
	set("id",({"sneakers","shoes","tennis shoes"}));
	set("short","A pair of tennis shoes");
	set("long","These tennis shoes may actually provide some decent protection "+
		"to your feet.");
	set_type("boots");
	set_ac(6);
	set_limbs(({"right foot","left foot"}));
	set_weight(101);
	set_value(51);
}
