// /wizards/excelsior/cape/inn/hall
// The hall leading to the inn rooms
// Excelsior 9-23-96

#include <std.h>
#define ROOMS 5

inherit "/std/vault";

void create() {
	int i;
string room;
	::create();
	set_property("light",2);
	set_property("indoors",1);
	set_property("no castle",1);
	set_property("no mine",1);
	set("short","In the hotel hallway");
	set("long","You are a hallway on the second level of the South Cape "+
		"Bed and Breakfast. This really is a qaint little place. The floors "+
		"are hard wood and a rickety old staircase leads back %^RED%^down%^RESET%^ "+
		"to the rest of the hotel. All around you are doors to the hotel's various "+
		"rooms. To unlock a door with your room key, type 'unlock door <room number> "+
		"with key'. There is a %^BOLD%^sign%^RESET%^ on the wall.");
	set_items(([({"hall","hallway"}):"A necessary utility in reaching the hotel "+
			"rooms.",
		"place":"It is very quaint.",
		"floors":"They are nice, smooth, hard wood. The craftsmenship is superb.",
		"wood":"Most of the building is wood.",
		"staircase":"It leads down to the main entrance of the inn.",
		"rooms":"They are all around you.",
		"sign":"You can %^RED%^read%^RESET%^ it.",
		({"doors","door"}):"They look fairly safe."]));
	i = 1;
	while(i <= ROOMS) {
		room = sprintf("%d",i);
		add_exit("/wizards/excelsior/cape/inn/room"+room,"room"+room);
		set_door("door "+room,"/wizards/excelsior/cape/inn/room"+room,"room"+room,
			"cape key "+room);
		set_lock_level("door "+room,15);
		i++;
	}
		add_exit("/wizards/excelsior/cape/inn/entrance","down");
}

void init() {
	::init();
	add_action("read","read");
}

int read(string str) {
	if(str != "sign") return 0;
	write(
"Welcome to South Cape Bed and Breakfast\n"+
"\nTo most enjoy your stay here, make use of the following commands:\n"+
"%^BLUE%^describe room%^RESET%^: If you are the owner of a room, you can "+
"customize its description with this command, while you are in the room.\n"+
"%^BLUE%^revert%^RESET%^: If you want to return to the boring generic inn room "+
"description, you can type this when in the room you own.\n"+
"To unlock your room number, refer to the door as 'door <room number>'\n"+
"%^GREEN%^Example:%^RESET%^ Unlock door 3 with key\n\n"+
"Be sure to check the inn gift shop for interesting items and fun things "+
"to do around South Cape!\n\nThank you for reading this sign.");
	return 1;
}
