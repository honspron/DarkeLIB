// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// War-Priest Guild Hall
// 10/05/96

#include <std.h>

inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("no castle", 1);
	set("short", "Hall of the Honoured");
	set("long",
		"A hallway leads eastward to the center of the Hall of the "
		"Honoured.  To the south is the hall treasury.  A donation of "
		"5 silver is asked of all members who wish to enter.\n"
	);
	set_exits( ([
		"east": "/d/damned/guilds/war-priest/hh5",
		"south": "/d/damned/guilds/war-priest/hh7"
	]) );
	set_door("treasury door", "/d/damned/guilds/war-priest/hh7", "south",
		0);
	set_open("treasury door", 0);
	set_locked("door", 0);
}

void reset() {
	::reset();
	if(!present("guard")) {
		new("/d/damned/guilds/war-priest/t_guard")->move(TO); }
}
