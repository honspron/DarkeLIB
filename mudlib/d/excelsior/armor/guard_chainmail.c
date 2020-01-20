// /wizards/excelsior/armor/guard_chainmail

inherit "/std/armour";

void create() {
	::create();
	set_name("chainmail");
	set("id",({"chainmail","guard chainmail","guards chainmail","guard's chainmail"}));
	set("short","A guards chainmail");
	set("long","This is a government employed guard's fine chainmail. It makes "+
		"its weary look very dignified and important.");
	set_type("body armour");
	set_ac(6);
        set_limbs( ({"torso"}) );
	set_weight( 201 );
	set_value( 523 );
}
