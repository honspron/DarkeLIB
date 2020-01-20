// /d/nfd/weapons/spear.c



inherit "/std/weapon";



void create() {

	::create();

	set_name("spear");

	set("short","guard's spear");

	set("id",({"spear","guards spear"}) );

	set("long","This is a ok guards spear. It looks very ok.");

	set_weight( 215 );

	set_value( 420 );

	set_ac( 1 );

	set_wc( 7, "impaling" );

	set_type( "two handed polearm" );

	set_quality( 4 );

}

