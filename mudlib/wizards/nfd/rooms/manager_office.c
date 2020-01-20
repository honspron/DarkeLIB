// /d/nfd/rooms/manager_office
// big bertha is a talker, she is

#include <std.h>

inherit ROOM;

void reset() {
	::reset();
	if (!present("bertha")) new("/d/nfd/mon/bertha")->move(
		this_object() );
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",1);
	set("short","In a converted dressing room");
	set("long","This dressing room has been converted into an office for the "+
		"theatre manager. There is a large desk to one side of the room flooded "+
		"with a metaphorical sea of paper. To your west is a hallway.");
	set_items( (["desk":"The theatre manager sits behind it.",
		"hallway":"You just came from there stupid." ]) );
	set_exits( (["west":"/d/nfd/rooms/dressing_rooms" ]));
}
