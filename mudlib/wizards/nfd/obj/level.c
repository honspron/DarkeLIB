// /d/nfd/obj/leveler

// this handy item will tell you they level of a monster 3 times.



#include <std.h>



inherit OBJECT;



int charges;



void init() {

	::init();

	add_action("find_level","scan");

}



void set_some_stuff() {

	set("long","This is a wooden bucket with a strange herbal "+

		"concaction contained with in. "+

	"A lable on the side explains it was developed by some mystical beings to find the level of "+

		"other living enteties. To use it type 'scan <living>'.");

	set_value( 95*charges );

}

	

void create() {

	::create();

	charges = 3;

	set_name("scanner");

	set("id",({"scanner","level scaner"}) );

	set("short","A fine level scanner");

	set_some_stuff();

	set_weight( 145 );

}



int find_level( string who ) {

	object guy;

	if (!who) {

		notify_fail("Scan who?\n");

		return 0;

	}

	if ( living( environment( this_object() ) ) ) {

		guy = present( who, environment( environment( this_object())));

	} else {

		guy = present( who );

	}

	if (!guy) {

		write("You need to scan someone in the same room as you.")

			;

		return 1;

	}

	else {

		write("You scan "+guy->query_cap_name()+", who you learn is a level "+

			guy->query_level()+" being.");

		charges--;

		set_some_stuff();

	}

	if (charges < 1) {

		write("The scanner is used up and it disentagrates.");

		this_object()->remove();

	}

	return 1;

}

		

