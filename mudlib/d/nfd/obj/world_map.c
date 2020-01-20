// /d/nfd/obj/world_map

// Excelsior 7-2-96



inherit "/std/Object";



void create() {

	::create();

	set_name("map");

	set("id",({"map","world map"}));

	set("short","A portable world map");

	set("long","This is a portable world map for the adventurer. "+

		"You probably want to 'read' it.");

	set_weight(50);

	set_value(50);

}



void init() {

	::init();

	add_action("read","read");

}



int read(string str) {

	if(!id(str)) {

		notify_fail("Read what?\n");

		return 0;

	}

	message("my_action","You examine your map.",this_player());

	this_player()->more("/wizards/mikus/world_map");

	message("other_action",(string)this_player()->query_cap_name()+

		" looks at "+(string)this_player()->query_possessive()+" map.",

		environment(this_player()),({this_player()}));

	return 1;

}

