inherit "/std/weapon";

create() {
	::create();
	set("id", ({"sword", "serrated sword"}) );
	set("short", "serrated sword");
	set("long",
		"With a wicked edge, this sword rips your foes apart."
	);
	set_weight(190);
	set_wc(18, "cutting");
	set_value(500);
	set_ac(4);
	set_type("blade");
	set_quality(5);
	set_verb("rip");
	set_parry_bonus(5);
}
