// /d/nfd/obj/sceptre



#include <std.h>



inherit OBJECT;



void init() {

	::init();

	add_action("make_pet","make");

}



void create() {

	::create();

	set_name("sceptre");

	set("id",({"magic sceptre","sceptre","createer"}) );

	set("short","A magic sceptre");

	set("long","This is a magical sceptre that can be used to create "+

		"a helpfull rock. If you would like to take advantage of "+

		"a rock's services you can 'make rock'.");

	set_weight( 420 );

	set_value( 6700 );

}



int make_pet( string str ) {

	object ob;

	seteuid(getuid());

	if ( str != "rock" ) {

		notify_fail("What do you wish to make?\n");

		return 0;

	}

	ob = new("/d/nfd/mon/living_toaster");

if ( living( environment(this_object()))) {

		ob->move( environment(environment(this_object())));

	} else {   ob->move( environment( this_object())); }

	ob->set_owner( this_player()->query_name() );

	write("You create a magical rock and your sceptre dissapears.");

	message("info","%^GREEN%^%^BOLD%^A rock appears, follower of "+

this_player()->query_cap_name()+".",environment( ob), ({}) );

	this_object()->remove();

	return 1;

}

