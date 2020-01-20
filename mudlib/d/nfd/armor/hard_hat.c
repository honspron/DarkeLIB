// /d/nfd/armor/hard_hat



inherit "std/armour";



void create() {

	::create();

	set_name("hard hat");

	set("id",({"hat","hard hat"}) );

	set("short","A workers hard hat");

	set("long","This is some kind of a hat that you surmise once belonged to a "+

	"city municipal employee. It looks as though it is good for protecting your head from low over hangs. You wonder why he (or she) would leave "+

	"such a nice looking hat lying around.");

	set_type("helmet");

	set_ac( 10 );

	set_limbs( ({"head"}) );

	set_weight(125);

	set_value(275);

}

