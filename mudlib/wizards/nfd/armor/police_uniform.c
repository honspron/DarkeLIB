// /d/nfd/armor/police_uniform



#include <std.h>



inherit ARMOUR;



void create() {

	::create();

	set_name("uniform");

	set("id",({ "uniform","police uniform"}) );

	set("short","A police uniform");

	set("long","This is a light blue police uniform. Though it is very "+

		"beautiful, you doubt that it will provide you with much protecttion.");

	set_type("body armour");

	set_ac( 1 );

	set_limbs(({"torso","left leg","right leg","left arm","right arm"}));

	set_weight( 95 );

	set_value( 5 );

}

