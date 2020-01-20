inherit "/std/weapon";

create() {
	::create();
	set("id", ({"huge morning star", "star", "morning star"}) );
	set("short", "huge morning star");
	set("long",
		"A large studded ball hangs from a heavy chain.  The "
		"prefered weapon of the Kuril Guard, this morning star "
		"is used with great efficacy to bludgeon their victims "
		"unconscious while avoided limb dismemberment."
	);
	set_weight(290);
	set_wc(18, "crushing");
	set_value(100);
	set_ac(3);
	set_type("two handed flail");
	set_quality(3);
	set_verb("pound");
	set_parry_bonus(-15);
}
