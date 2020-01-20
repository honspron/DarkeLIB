// /wizards/excelsior/cape/rooms/rm2
// more fun

#include <std.h>

inherit "/std/room";

int door;

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",0);
	set("short","A cobblestone road");
	set("long","The cute dirt path you were travelling has transformed "+
		"into a cute little cobble stone path. You continue "+
		"to marvel at the excellent shape this place is kept in. To the east "+
		"you can see the small town of South Cape. Past the town you can see "+
		"the ocean, blue and beautiful. The sea breeze blows through your hair "+
		"and you realize this would be a wonderful place to retire to.");
	set_items((["path":"Something about the path bothers you.",
		({"town","south cape"}):"It looks very peaceful. What a happy place!",
		({"ocean","sea"}):"This place is after all a coastal fishing villiage!"]));
	set_listen("default","You hear the surf in the distance.");
	set_smell("default","You smell that ocean smell that a lot of people think stinks "+
		"but you rather enjoy.");
	set_search("path","You discover one of the cobble stones to be loose! Perhaps "+
		"you could pull it out.");
	set_exits((["north":"/wizards/excelsior/cape/rooms/entrance",
		"east":"/wizards/excelsior/cape/rooms/town1"]));
	door = 0;
}

void init() {
	::init();
	add_action("pull","pull");
}

int pull(string str) {
	if(str == "stone" || str == "cobblestone") {
		if(door) {
			write("The secret door is already open!");
			return 1;
		}
		write("You pull on the loose stone and part of the road slides open, "+
			"revealing an entrance to the underworld!");
		message("other_action",(string)this_player()->query_cap_name()+" pulls "+
			"on a loose cobblestone, and to your utter amazement a doorway "+
			"opens in the ground!",this_object(),({this_player()}));
		add_exit("/wizards/excelsior/cape/rooms/under2","down");
		add_item("door","It just opened in the middle of the road! How odd!");
		door = 1;
		call_out("close_door",10);
		return 1;
	}
	notify_fail("You pull and pull your hair, to no avail!\n");
	return 0;
}

void close_door() {
	message("info","The door in the ground slides shut, leaving no trace that it "+
		"was ever there.",this_object());
	remove_exit("down");
	remove_item("door");
	door = 0;
}	
