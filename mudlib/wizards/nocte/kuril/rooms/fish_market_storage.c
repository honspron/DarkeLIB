#include <std.h>
#include <nevin.h>
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", 1);
	set("short", "Fish Market Storage Room");
	set("long",
		"Oh the smell!  You start to feel abit light-headed from "
		"the stench in this room.  Do they ever clean up in here?"
	);
	set_exits( ([
		"east": "fish_market"
	]) );
	set_items( ([
		({"metal door", "door"}): (: call_other, this_object(), "look_door" :)
	]) );
	set_smell("default", "The smell of dead fish is overpowering in " +
		"this room.");
	set_door("metal door", ROOMS+"fish_market", "east",
		"kuril fish market storage key");
	set_open ("metal door", 0);
	set_locked("metal door", 1);
	set_lock_level("metal door", 25);
	set_property("storage room", 1);
	return;
}

void reset() {
	object *inv, ob;
	int i;

	::reset();
	seteuid(getuid());
	inv = all_inventory(this_object());
	while(i--) if(!living(inv[i])) inv[i]->remove();
	for(i=1; i<=20;i++) {
		new(MISC+"salted_herring")
			->move(this_object());
		new(MISC+"makeral")
			->move(this_object());
		new(MISC+"tuna")
			->move(this_object());
		new(MISC+"flounder")
			->move(this_object());
		new(MISC+"perch")
			->move(this_object());
	}
	return;
}

void look_door() {
	if(query_open("metal door")) {
		write("The metal door is open.");
	}
	else {
		write("The metal door is closed.");
	}
}
