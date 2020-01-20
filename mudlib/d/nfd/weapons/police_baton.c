// /d/nfd/weapons/police_baton



inherit "std/weapon";



void create() {

	::create();

	set_name("baton");

	set("id",({"police baton","baton"}) );

	set("short","police baton");

        set("long","This is a one-handed police baton "

          "used for beating rioters."

        );

	set_weight( 201 );

	set_value( 350 );

	set_ac( 5 );

	set_wc(8, "stress" );

	set_type("blunt");

	set_quality(4);

}

