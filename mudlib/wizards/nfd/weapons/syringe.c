// a nifty weapon for doctors

// /d/nfd/weapons/syringe



inherit "std/weapon";



void create() {

	::create();

	set("id",({"syringes","doctor's syringes"}));

	set_name("syringes");

	set("short","Some doctor's syringes");

	set("long","These are some doctors syringes that are normally "+

		"used to cure, but can also be used to hurt. Hey, nobody "+

		"likes shots, right? In fact, these syringes are filled "+

		"with a deadly disease, so they act as a poison weapon as "+

		"well.");

	set_wc(4,"impaling");

	set_ac(1);

	set_throwable(1);

	set_type("knife");

	set_quality(3);

	set_wield("You feel like giving people shots as you wield the "+

		"syringes.");

	set_property("no add quality",1);

	add_poisoning( random(13) + 2 );

	set_parry_bonus( -25 );

	set_value( 75 );

	set_weight( 120 );

}

