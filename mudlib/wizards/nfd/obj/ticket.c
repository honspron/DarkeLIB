// /d/nfd/obj/ticket

// one pass to the show!



inherit "std/Object";



void init() {

	::init();

	add_action("read_note","read");

}



void create() {

	set_name("ticket");

	set_id(({"ticket","a ticket"}) );

	set_short("A ticket to the show");

	set_long("This is a mighty fine ticket to a theater somewhere. "+

		"You could probably 'read' it.");

	set_value( 350 );

	set_weight( 50 );

}



int read_note(string str) {

if ( this_object()->id(str) ) {

	write("***************************************************\n"+

"*   New Faerie Dust Theatre Company               *\n"+

"*                                                 *\n"+

"*   Good for one admission to any show            *\n"+

"*                                                 *\n"+

"*                        J6 row 7                 *\n"+

"***************************************************");

		return 1;

		}

	else {

		notify_fail("Read what?");

		return 0;

	}

}

