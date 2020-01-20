// /d/nfd/obj/transporter



#include <std.h>



inherit OBJECT;



void init() {

	::init();

	add_action("go_home","press");

}



void create() {

	::create();

	set_name("bottle");

	set("id",({"milk bottle","bottle","magic bottle","magic milk bottle"}) );

	set("short","A magical milk bottle");

	set("long","This magical milk bottle contains no milk at all. It is a "+

		"transporter device built by the sewer cows. You read a small note "+

		"on the side: \"This device will return you to somewhere safe. "+

		"To use is, simply press the large red button.\" There is indeed "+

		"a large red button sticking out of the opening.");

	set_weight( 95 );

	set_value( 450 );

}



int go_home( string str ) {

	if (str == "button") {

	  if(this_player()->query_level() > 6) {

                write("You are too high level and you crush the bottle");

                this_object()->remove();

                return 1;

	  }

              else

		write("You press the button and appear elsewhere. A strange reaction has taken place inside the bottle. The milk bottle, "+

			"having been used up, disentagrates.");

		this_player()->move_player( "/d/standard/square");

		this_object()->remove();

		return 1;

	}

	notify_fail("Press button!\n");

	return 0;

}

