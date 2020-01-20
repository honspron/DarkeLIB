// /d/nfd/obj/curtain_obj

// pure fun. If you don't think it's fun, you suck

// Excelsior



inherit "std/Object";



string state;



void set_state(string state_ent) {

	string time_curtain_message,guy_squashed_message;

	object actor_dude;

	int fun_chance;

	actor_dude = present("actor",environment(this_object()));

	if (state_ent == "curtain") {

		this_object()->set_short("The front curtain has been lowered");

		if (query_night()) {

			if (actor_dude) {

			time_curtain_message = "This is rather stupid because "+

			"an actor is orating his part to the closed curtain. "+

			"Someone has really blown it."; }

			else { time_curtain_message = "This is ok because no "+

				"actor is currently on the stage. Where could he "+

				"be?"; 

				}

			}

		else {

		time_curtain_message = "This is ok because no play is "+

		"scheduled to be being performed right now.";

		}

		this_object()->set_long("Some one has lowered the curtain "+

		"blocking the view anyone in the seats to the south may have been "+

		"enjoying. "+time_curtain_message);

		this_object()->set_property("keep","  ");

		state = state_ent;

		return;

		}

	if (state_ent == "bag") {

		this_object()->set_short("A fallen sand bag");

		if (actor_dude) {

			fun_chance = random(3);

			if (random(3) == 2) {

				guy_squashed_message = "Somebody stupidly let "+

					"it fall without clearing the stage first. "+

					"It apparently landed on an actor who was "+

					"performing his part.";

					actor_dude->die();

					environment(this_object())->actor_die();

				}

			else {

				guy_squashed_message = "Somebody carelessly let "+

				"fall without clearing the stage first. Luckily "+

				"it just missed the actor that is here.";

			}}

		else {

			guy_squashed_message = "It fell, but it appears nobody "+

			"was on the stage when it happened, so no one was hurt.";

		}

		this_object()->set_long("This is a large sand bag that looks "+

			"like it came from a theatre- it is the thing that "+

			"counter weights the curtains to make them easier to "+

			"raise. "+guy_squashed_message);

		state = state_ent;

		return;

	}

}

	

string query_state() {

	return state;

}	



void create() {

	::create();

	set_name( "curtain" );

	set_weight(400);

	set_property("keep","   ");

	set_value(13);

	set_id( ({"curtain","bag","sand bag"}) );

}



