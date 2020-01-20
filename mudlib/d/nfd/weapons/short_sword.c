// /d/nfd/weapons/short_sword



inherit "std/weapon";



void create() {

	::create();

	set_name("sword");

	set("id",({"short sword","sword","boring short sword"}) );

	set("short","short sword");

	set("long","Quite a boring and ugly short sword. It looks like it "+

	"has been sitting in a sewer for a while.");

	set_weight( 310 );

	set_value( 75 );

	set_ac( 4 );

	set_wc( 3, "cutting" );

	set_type("blade");

	set_quality(2);

}

