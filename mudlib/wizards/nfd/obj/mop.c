// /d/nfd/obj/mop



// a mop.



inherit "std/Object";

void init() {

	::init();

	add_action("mop_it","pretend");

}



void create() {

	::create();

	set_name("mop");

	set_id( ({"mop","broom","cleaning tool","cleaning utensil"}) );

	set("short","A lost mop");	set("long","This is a mop that somebody foolishly left lying around. They "+

		"should have known better then to leave a valuable item like THIS "+

		"just sitting out in the open. You dream of using this mop to become "+

		"a janitor. Hrm. Well, maybe you could atleast PRETEND to be a janitor.");

	set_value(7);

	set_weight(30);

}



int mop_it(string str) {

	if (str = "to be a janitor" || str = "janitor") {

	write("You fantasize about being a janitor. You use your mop and start cleaning "+

	"up the area around you.");

	tell_room(environment( this_player() ), this_player()->query_cap_name() + " uses "+

	"a mop wisely.", ({ this_player() }) );

	return 1;

}

	notify_fail("Pretend to be what?\n");

	return 0;

}

