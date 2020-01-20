// /wizards/excelsior/cape/rooms/town3

#include <std.h>

inherit "/std/vault";

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",0);
	set("short","A road through town");
	set("long","You are traveling along a cobblestone road through the "+
		"heart of South Cape. There are a few beings around going about "+
		"their normal business, but not that many. It is very quiet and "+
		"pleasant here. To the north there is a sign reading \"Bob the "+
		"Money Changer\" while to the east is a sign reading \"Bob's "+
		"General Store\". Hrm, this Bob must be a rich fellow! The road "+
		"continues south and up a small slope to the northwest. The wall of "+
		"the town inn blocks any movement west.");
	set_items((["bob":"You sure would like to meet him!",
		({"sign","signs"}):"They designate the names of the stores so as "+
			"to prevent confusion.",
		"road":"To the south it goes to Town Square, while to the northwest "+
			"it travels up a short incline.",
		
		"store":"You can probably take care of most of your economic needs "+
			"at that establishment.",
		"beings":"They don't disturd your environment in the least. In fact, "+
			"they are practically part of it.",
		"cobblestone":"The road is made of these.",
		"here":"As opposed to there.",
		"inn":"Probably not a bad place to stay.",
		"wall":"A wall!!! WTF?!?!?! The nerve!!",
		({"slope","incline"}):"It is a well placed incline and makes the town "+
			"all the more pleasant. The road goes straight up the few feet the "+
			"slope has to offer without a second thought. What is a quaint little "+
			"village without a few well placed hills?"]));
	set_exits((["north":"/wizards/excelsior/cape/rooms/money_changer",
		"east":"/wizards/excelsior/cape/rooms/general_store",
		"south":"/wizards/excelsior/cape/rooms/town2",
		"northwest":"/wizards/excelsior/cape/rooms/town4"]));
	set_door("south door", "/wizards/excelsior/cape/rooms/money_changer", "north", "ms out");
    set_open("south door", 1);
    set_open("south door", 1);
    set_locked("south door", 0);
    set_open_function("open_door", "1:00:00");
    set_close_function("close_door", "17:00:00");
}

void close_door() {
  call_other("/wizards/excelsior/cape/rooms/money_changer", "close_door");
  return;
}

void open_door() {
  call_other("/wizards/excelsior/cape/rooms/money_changer", "open_door");
  return;
}
