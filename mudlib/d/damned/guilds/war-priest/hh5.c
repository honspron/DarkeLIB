// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// War-Priest Guild Hall
// 10/05/96

#include <std.h>

inherit "/std/room";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("no castle", 1);
	set("short", "Hall of the Honoured");
	set("long",
		"You are standing at the center of the Hall of the "
		"Honoured.  Large tapestries hang from the tall walls which "
		"rise up around you.  As you walk within the hall, your "
		"footsteps echo off the stone walls.  To the north is an "
		"altar to K'thach, patron of this hall.  To the west is a "
		"hallway.  To the east is a small library and to the south "
		"is the entrance to the hall."
	);
	set_exits( ([
		"north": "/d/damned/guilds/war-priest/hh2",
		"east": "/d/damned/guilds/war-priest/hh6",
		"south": "/d/damned/guilds/join_rooms/war-priest_join",
		"west": "/d/damned/guilds/war-priest/hh4"
	]) );
}
