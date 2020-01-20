#include <std.h>
#include "nevin.h"
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("night light", 0);
	set_property("no castle", 1);
	set("short", "Adventurer's Shop Storage Room");
	set("long",
		"Fine examples of Dnerr's handiwork are stored here for "
		"sale in his shop."
	);
	set_exits( ([
		"south": "general_store"
	]) );
	set_items( ([
		({"wooden door", "door"}): (: call_other, this_object(), "look_door" :),
		({"work", "examples"}): "Why don't you ask Dnerr about them?"
	]) );
	set_door("wooden door", ROOMS+"general_store",
		 "south", "kuril leather shop key");
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
	for(i=1; i<=5;i++) {
		new(MISC+"oil")->
			move(this_object());
		new(MISC+"sextant")->
			move(this_object());
		new(MISC+"lantern")->
			move(this_object());
		new(MISC+"torch")->move(TO);
		new(MISC+"bag")->
			move(this_object());
		if(i < 4) { new(MISC+"fishing_pole")->move(TO); }
		if(i < 2) { new(MISC+"shovel")->move(TO); }
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
