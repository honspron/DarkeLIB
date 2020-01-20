// /d/nfd/rooms/shops/office
// a useful place indeed

inherit "/std/room";

int came;

void reset() {
	::reset();
	came = 0;
}

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",1);
	set("useful",1);
	set("short","The New Faerie Dust Government Support room");
	set("long","This is a unique room. Here, many useful things are "+
		"sold to government employees at super cheap prices. "+
		"Merchandise includes maps, "+
		"useful devices and more! It is just like the government to "+
		"hog this wonderful service for itself. There is a counter here "+
		"with a %^BLUE%^bell%^RESET%^ on it");
	set_items((["counter":"It is very professional looking. It has a bell on it.",
		"room":"You are in a room.",
		"bell":"Attached is a small note that says 'for service ring bell'"]));
	set_exits((["west":"/d/nfd/rooms/level3/building3"
		]));
}

void init() {
	::init();
	add_action("ring","ring");
}

int ring(string str) {
	object ob;
	if(str != "bell") {
		notify_fail("Ring what?\n");
		return 0;
	}
	message("other_action",(string)this_player()->query_cap_name()+" rings "+
		"the bell.",this_object(),({ this_player() }));
	message("my_action","You ring the bell.",this_player());
	if(!present("clerk") && came == 1) {
		write("You ring and ring the bell but no one comes! Could someone have died?");
		return 1;
	}
	ob = present("clerk");
	if(ob) {
		ob->set_primary_lang((string)this_player()->query_primary_lang());
		if(!(string)ob->query_primary_lang()) ob->set_primary_lang("common");
		message("info","The clerk bogs.",this_object());
		ob->force_me("say I'm already here.");
		return 1;
	}
	ob = new("/d/nfd/rooms/shops/office_clerk")
;
	ob->move(this_object());
	message("info","A clerk runs in, looking for someone to help.",this_object());
	ob->set_primary_lang((string)this_player()->query_primary_lang());
	if(!(string)ob->query_primary_lang()) ob->set_primary_lang("common");
	ob->force_me("say Can I help you?");
	came = 1;
	return 1;
}
