#include <std.h>
#include "nevin.h"
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", 1);
	set("short", "Book Binder Shop Storage Room");
	set("long",
		"Protected from the elements in this small storage closet, "
		"books hand made by Rety await purchase."
	);
	set_exits( ([
		"south": ROOMS+"book_binder"
	]) );
	set_items( ([
		({"wooden door", "door"}): (: this_object(), "look_door" :)
	]) );
	set_door("wooden door", "book_binder", "north", "kuril book binder
		shop storage");
	set_open ("wooden door", 0);
	set_locked("wooden door", 1);
	set_lock_level("wooden door", 25);
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
	for(i=1; i<=1;i++) {
		new(MISC+"kuril_book")->
			move(this_object());
	}
	return;
}

void look_door() {
	if(query_open("wooden door")) {
		write("The wooden door is open.");
	}
	else {
		write("The wooden door is closed.");
	}
}
