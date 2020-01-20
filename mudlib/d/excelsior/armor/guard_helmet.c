// /wizards/excelsior/armor/guard_helmet

inherit "/std/armour";

void create() {
	::create();
	set_name("helmet");
	set("id",({"helmet","spartan helmet","guard's helmet","guard helmet",
		"guards helmet"}) );
	set("short","A guard's greek looking helmet");
	set("long","The designer of this helmet built for a government employed "+
		"guard has obviously studied Greek armour designs. You might be able "+
		"to sell it as an authentic antique if it weren't for the large "+
		"insignia on the helmet's side saying: 'This is not an authentic "+
		"Spartan helmet");
	set_type("helmet");
	set_ac(6);
	set_limbs( ({"head"}) );
	set_weight( 250 );
	set_value( 444 );
}
