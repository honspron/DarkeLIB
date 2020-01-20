// /d/nfd/armor/dark_cloak



inherit "std/armour";



void create() {

	::create();

	set_name("cloak");

	set("id",({"dark cloak","the dark cloak","cloak of darkness","the cloak "+

		"darkness"}) );

	set("short","The cloak of darkness");

	set("long","This is the type of cloak worn by the masked theatre-ghost "+

		"type. It is made out of very fine fabric, and though it doesn't "+

		"look magical, you can feel that it is much better armour then "+

		"it appears to be at first glance.");

	set_type("cloak");

	set_ac(5);

	set_limbs( ({"torso","right arm","left arm","right leg","left leg",

		}) );

	set_weight(95);

	set_value(495);

}

