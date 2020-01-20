#include <std.h>
#include "nevin.h"
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", 1);
	set("short", "Bakery Shop Storage Room");
	set("long",
		"On still hot baking trays are the goods to be sold in the "
		"bakery."
	);
	set("night long",
		"Leftover breads and pastries from the day's sales have been "
		"left here.  Rebecca gives them to the poor every morning."
	);
	set_exits( ([
		"south": ROOMS+"bakery"
	]) );
	set_items( ([
		({"pantry door", "door"}): (: call_other, this_object(), "look_door" :),
		"pantry": (: call_other, this_object(), "look_door" :)
	]) );
	set_smell("default", "Your mouth begins to water at the scent of the " +
		"delicious smelling baked goods.");
	set_door("pantry door", "bakery", "south", "kuril bakery 
		storage key");
	set_open ("pantry door", 0);
	set_locked("pantry door", 1);
	set_lock_level("pantry door", 25);
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
	for(i=1; i<=30;i++) {
		new(MISC+"roll")
			->move(this_object());
		new(MISC+"loaf")
			->move(this_object());
		new(MISC+"cake")
			->move(this_object());
		new(MISC+"cookie")
			->move(this_object());
	}
	return;
}

void look_door() {
	if(query_open("pantry door")) {
		write("The pantry door is open.");
	}
	else {
		write("The pantry door is closed.");
	}
}
