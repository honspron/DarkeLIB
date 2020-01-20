// /wizards/excelsior/cape/rooms/town2
// town square

#include <std.h>

inherit ROOM;

int door;

void reset() {
	::reset();
}

void init() {
	::init();
	add_action("read","read");
	add_action("open","open");
}

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",0);
	set("short","Town square");
	set("long","You are in the clean and well kept town square of South Cape. "+
		"This is certainly a sleepy little town. For all its beauty there is "+
		"practically nobody about. In the center of the square is a large "+
		"%^BLUE%^fountain%^RESET%^. The fountain depicts several large "+
		"fish wreathing about a forboding figure holding a trident. On one "+
		"side of the fountain is a large %^YELLOW%^%^BOLD%^plaque%^RESET%^ "+
		"while on the other side are some sturdy looking %^GREEN%^vault doors"+
		"%^RESET%^. To the north the road through town continues, to the south "+
		"is the 'Big Fish Pub' and to the east is a pier.");
	set_items((["fountain":"It is a rather impressive piece of art. You wonder "+
			"what it means. The people of South Cape certainly have good taste.",
		"figure":"It is a large and powerful looking figure, almost god like. "+
			"Who could it be?",
		"plaque":"You may be able to 'read' the plaque.",
		"fish":"Don't worry, they aren't REAL fish, it is just a statue.",
		"road":"The road goes west and north",
		"pub":"Doesn't look half bad...",
		({"doors","vault doors"}):"There are several large gears with numbers etched into them on the doors. You wonder how you could open them."
,
		"pier":"All coastal villages have a pier."]));
	set_exits((["north":"/wizards/excelsior/cape/rooms/town3",
		"west":"/wizards/excelsior/cape/rooms/town1",
		"south":"/wizards/excelsior/cape/rooms/pub",
		"east":"/wizards/excelsior/cape/rooms/pier"]));
	door = 0;
}

int read(string str) {
	if(str != "plaque") {
		notify_fail("Read what?\n");
		return 0;
	}
	write("%^ORANGE%^%^BOLD%^The wonderful town of %^GREEN%^South Cape%^RESET%^\n"+
		"\nBrought to you through the efforts of\n\n%^BLUE%^%^BOLD%^Excelsior%^RESET%^ "+
		"the magnificent\n\n");
	return 1;
}

int open(string str) {
	if(str == "doors" || str == "door" || str == "vault door") {
		if(door) {
			notify_fail("The vault doors have already been opened.\n");
			return 0;
		}
		write("You try to open the doors, but they won't open unless the gears "+
			"are aligned properly. How do you want to align the gears?");
		message("Ninfo","Enter the 3 digit gear code now: ",this_player());
		input_to("open_door");
		return 1;
	}
	notify_fail("What do you wish to open?\n");
	return 0;
}

void open_door(string str) {
	if(strlen(str) > 3) {
		write("You try to align the gears to "+str+" but can't figure out how.");
		return;
	}
	if(str != "411") {
		write("You align the gears to "+str+" but the doors will not budge!");
		return;
	}
	write("You align the first gear to 4, the second to 1, and the third to 1. The "+
		"vault doors suddenly fly open, revealing a dark stairway leading down.");
	message("info","The vault doors on the side of the fountain suddenly fly open!",
		this_object());
	add_exit("/wizards/excelsior/cape/rooms/vault","down");
	door = 1;
	call_out("close_door",10);
	return;
}

void close_door() {
	remove_exit("down");
	message("info","The vault doors slam shut.",this_object());
	door = 0;
	return;
}
