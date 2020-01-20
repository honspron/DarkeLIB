// /d/nfd/rooms/emporium/foyer

#include <std.h>

inherit ROOM;

void reset() {
	::reset();
	if(!present("news board"))
		new("/d/nfd/obj/emporium/news_board")->move(this_object());
	if(!present("arrow sign"))
		new("/d/nfd/obj/emporium/dir_sign")->move(this_object());
}

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",1);
	set("short","In the Excelsior Emporium");
	set("long","This is the major entertainment center in new faeriedust. "+
		"Here is a place where citizens and guests of the city come to get "+
		"information, socialize, gamble and play games. This is the place "+
		"to be.");
	set_exits((["south":"/d/nfd/rooms/square",
		"west":"/d/nfd/rooms/emporium/library",
		"east":"/d/nfd/rooms/emporium/newbie",
		"north":"/d/nfd/rooms/emporium/board",
		"northwest":"/d/nfd/rooms/emporium/casino",
		"northeast":"/d/nfd/workroom"]));
	add_pre_exit_function("northwest","sorry");
	add_pre_exit_function("northeast","check_wiz");
	reset();
}

int sorry() {
	write("A security guard informs you that the casino is still under construction.");
	return 0;
}

int check_wiz() {
	if(wizardp(this_player())) return 1;
	write("A security guard blocks you informing you that only wizards may go this "+
		"way.");
	return 0;
}
