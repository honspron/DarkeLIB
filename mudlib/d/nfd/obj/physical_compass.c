// /d/nfd/obj/physical_compass

// Excelsior 7-3-96



inherit "/std/Object";



void create() {

	::create();

	set_name("compass");

	set("id",({"compass","physical compass"}));

	set("short","physical compass");

	set("long","This objects uses magents to help you find your position "+

		"You should be able to find your way home if you want to 'locate' "+

		"yourself.");

	set_weight(90);

	set_value(100);

}



void init() {

	::init();

	add_action("locate","locate");

}



int locate(string str) {

	int x,y;

	string file;

	if(str) return 0;

	file = file_name(environment(this_player()));

	if(sscanf(file,"/d/damned/virtual/room_%d_%d.world",x,y) != 2) {

		write("You have to be on the island to use the compass.");

		return 1;

	}

	x = x - 15;

	y = y - 15;

	message("other_action",(string)this_player()->query_cap_name()+" fiddles "+

		"with a compass.",environment(this_player()),({this_player()}));

	if(x == 0 && y == 0) {

		write("You are at Akkad!");

		return 1;

	}

	if(x == 0 && y > 0) {

		write("You figure Akkad is directly to your north.");

		return 1;

	}

	if(x == 0 && y < 0) {

		write("You figure Akkad is directly to your south.");

		return 1;

	}

	if(y == 0 && x > 0) {

		write("You figure Akkad is directly to your west.");

		return 1;

	}

	if(y == 0 && x < 0) {

		write("You figure Akkad is directly to your east.");

		return 1;

	}

	if(y < 3 && y >-3 && x > 0) {

		write("You figure Akkad to be roughly to your west.");

		return 1;

	}

	if(y < 3 && y >-3 && x < 0) {

		write("You figure Akkad to be roughly to your east.");

		return 1;

	}

	if(x < 3 && x >-3 && y > 0) {

		write("You figure Akkad to be roughly to your north.");

		return 1;

	}

	if(x < 3 && x >-3 && y < 0) {

		write("You figure Akkad to be roughly to your south.");

		return 1;

	}

	if(x > 0 && y > 0) {

		write("You figure Akkad to be to your northwest.");

		return 1;

	}

	if(x > 0 && y < 0) {

		write("You figure Akkad to be to your southwest.");

		return 1;

	}

	if(x < 0 && y < 0) {

		write("You figure Akkad to be to your southeast.");

		return 1;

	}

	if(x < 0 && y > 0) {

		write("You figure Akkad to be to your northeast.");

		return 1;

	}

}

