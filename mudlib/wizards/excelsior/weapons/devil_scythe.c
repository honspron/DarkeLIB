// /wizards/excelsior/weapons/devil_scythe
// for lucifer

inherit "/std/weapon";

void create() {
	::create();
	set("id",({"scythe","the devil's scythe","devils scythe","devil's scythe","devil scythe"}));
	set_name("scythe");
	set("short","The Devil's Scythe");
	set("long","This is a deadly weapon indeed. Fashioned for the devil himself, he "+
		"decided he didn't need it and gave it to Lucifer the evil rhinocerous.");
	set_weight(200);
	set_value(9555);
	set_ac(5);
	set_wc(5,"cutting");
	set_type("Two handed polearm");
	set_quality(6);
	set_material("/metal/platnite");
}
