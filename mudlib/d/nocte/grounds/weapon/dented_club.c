inherit "/std/weapon";

create() {
	::create();
	set("id", ({ "club", "dented club" }) );
	set_name("club");
	set("short", "dented club");
	set("long",
		"This club has seen too many fights to be an effective weapon."
	);
	set_weight(15);
	set_value(30);
	set_wc(5, "crushing");
	set_ac(1);
	set_type("blunt");
	set_quality(1);
	set_decay_rate(50);
	set_wield("Your hands slips from the worn grip of the club, but you manage to catch it before it falls to the ground.");
	set_unwield("You gladly remove the club before it gets you killed.");
}
