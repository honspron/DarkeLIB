// /d/nfd/obj/star_key



inherit "std/Object";



void create() {

	::create();

	set_name("key");

	set("id",({"key","star key"}) );

	set_short("The star key");

	set_long("This is a normal looking key with a star carved in its "+

	"top. I wonder what secrets it unlocks..");

	set_weight(30);

	set_value(3);

}



