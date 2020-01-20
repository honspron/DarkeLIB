inherit "/std/food";

void create() {
	::create();
	set_name("makeral");
	set_my_mess("The makeral tastes great and is good for you too.");
	set_id( ({ "makeral", "fish" }) );
	set_short("A freshly caught makeral");
	set_strength(40);
	set_long("Fresh from the net of a local fisherman, the makeral is a "
		"healthy addition to your diet.");
	set_weight(7);
	set_value(20);
	return;
}
