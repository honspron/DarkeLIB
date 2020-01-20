#include <std.h>
#include <nevin.h>
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", 1);
	set("short", "Candle Shop Storage Room");
	set("long",
		"Candles of all shapes and sizes lines the walls of this "
		"small back room storage closet."
	);
	set_exits( ([
		"south": "candle_shop"
	]) );
	set_items( ([
		({"wooden door", "door"}): (: call_other, this_object(), "look_door" :)
	]) );
	set_door("wooden door", "candle_shop", "south", "kuril candle 
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
	for(i=1; i<=10;i++) {
		ob = new(MISC+"small_candle");
		ob->move(this_object());
		new(MISC+"large_candle")->move(TO);
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




