// /wizards/excelsior/obj/security_card

inherit "/std/Object";

void create() {
	::create();
	set_name("card");
	set("id",({"omega","security card","omega card","card","omega level security card"}));
	set("short","omega level security card");
	set("long","This is a forged omega level security clearance card. Though "+
		"forged, the craftsmenship is excellent and it should be good enough "+
		"to get you in most anywhere.");
	set_weight(25);
	set_value(300);
}
