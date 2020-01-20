// /wizards/excelsior/newbie/rooms/fr4.5

inherit "std/room";

int drank, sat;

void reset() {
	object mon;
	int n;
	::reset();
	drank = 0;
	sat = 0;
	for(n = 1;n < 6;n++) {
		if(!present("halfling "+n)) {
			mon = new("/wizards/excelsior/newbie/mon/halfling");
			mon->set_money("silver",1);
			mon->move(this_object());
		}
	}
}

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",1);
	set_property("no castle",1);
	set("short","In a house");
	set("long","You are in the cozy little abode of some inhabitant of this "+
		"peaceful and beautiful forest. There is a cute table here, a chair by "+
		"the table, and a bed off to one side. "+
		"You wish you could spend the rest of "+
		"your life here!");
	set_smell("default","You smell porridge steaming on a table.");
	set_items((["porridge":"Hrm. Maybe you could 'eat' some porridge! Yum!",
		"table":"There is a bowl of porridge on it.",
		"chair":"Maybe you could 'sit' in the chair.",
		"bed":"Perhaps you can 'lie' on the bed.",
		"fire":"You remember that fire is hot and decide not to touch it.",
		]));
	set_exits((["north":"/wizards/excelsior/newbie/rooms/fr4.4"
		]));
}

void init() {
	::init();
	add_action("eat","eat");
	add_action("sit","sit");
	add_action("lie","lie");
}


int eat(string str) {
	if(str[0..3] != "pori") {
		notify_fail("What food substance do you wish to consume?\n");
		return 0;
	}
	if(drank) { 
		write("Doh! Someone has been eating your porridge, and its all gone!");
		return 1;
	}
	write("You enjoy the porridge. The temperature is just right.");
	message("info",(string)this_player()->query_cap_name()+" eats some porridge.",environment(this_player()),({this_player()}));
	drank = 1;
	this_player()->set_hp((int)this_player()->query_max_hp());
	return 1;
}

int sit(string str) {
	if(str[0..3] == "chai" || str[0..3] == "on c" ){
		if(sat) { 
			write("Doh! Someone has been sitting in your chair, and its broken!");
			return 1;
		}
		write("You sit on the chair and enjoy your rest, but it soon breaks under "+
			"your weight.");
		message("info",(string)this_player()->query_cap_name()+" sits on a chair, but it breaks under "+(string)this_player()->query_possesive_pronoun()+" large girth.",environment(this_player()),({this_player()}));
		sat = 1;
		this_player()->add_hp(-random(2));
		return 1;
	} else {
		notify_fail("On which object do you wish to sit?\n");
		return 0;
	}
}

int lie(string str) {
	if(str[0..2] == "bed" || str[0..3] == "on b" ){
		write("You lie down on the bed to rest, but it is too hard for your liking.");
		message("info",(string)this_player()->query_cap_name()+" lies down on the bed.",environment(this_player()),({this_player()}));
		return 1;
	} else {
		notify_fail("On which object do you wish to sit?\n");
		return 0;
	}
}
