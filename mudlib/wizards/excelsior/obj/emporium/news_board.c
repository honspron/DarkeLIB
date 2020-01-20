// /wizards/excelsior/obj/emporium/news_baord

#include <std.h>

inherit OBJECT;

void init() {
	::init();
	add_action("read","read");
}

void create() {
	::create();
	set_name("board");
	set("id",({"board","news board","sign"}));
	set("short","An area announcements board");
	set("long","This is a board on which wizard types post information "+
		"on this area. You might be able to 'read' this board.");
	set_weight(1000000);
	set_value(800000);
}

int read(string str) {
	string room,*people;
	room = "/wizards/excelsior/rooms/faeriedust";
	if (present(str) != this_object()) {
		notify_fail("Read what?");
		return 0;
	}
	write("You read the board:");
	this_player()->more("/wizards/excelsior/doc/area_news");
	people = room->query_property("read news");
 	room->set_property("read news",people += ({ (string)this_player()->query_name() }) );
	return 1;
}
