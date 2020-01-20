// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

inherit "/std/weapon";

create() {
	::create();
	set("id", ({"cleaver"}) );
	set("short", "huge meat cleaver");
	set("long",
		"Good for chopping up pieces of meat.  The many chips and "
		"dents in the blade saw that this cleaver has cut through "
		"many a bone."
	);
	set_weight(60);
	set_wc(12, "cutting");
	set_value(20);
	set_ac(0);
	set_type("blade");
	set_quality(3);
	set_verb("slice");
	set_parry_bonus(-5);
}
