#include <std.h>
#include <nevin.h>
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", 0);
	set_property("no castle", 1);
	set("short", "Parchment Shop Storage Room");
	set("long",
		"This is the Butcher Shop Storage Room.  Lupo would "
		"definitely not want you back here.  The goods sold "
		"in Lupo's shop are stored here...I don't think he "
		"would want you back here."
	);
	set_exits( ([
		"north": "parchment_shop"
	]) );
	set_items( ([
		({"metal door", "door"}): (: this_object(), "look_door" :)
	]) );
	set_door("metal door", "butcher_shop.c", "north", "kuril butcher 
		shop storage");
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
	for(i=1; i<=10;i++) {
		new(MISC+"spell_scroll.c")->
			move(this_object());
	}
	return;
}

int look_door(string str) {
	if(!str) { return 0; }
	if( (str == "metal door") || (str == "door") ) {
		if(query_open("metal door")) {
			write("The metal door is open.");
			return 1;
		}
		else { write("The metal door is closed."); }
	}
}
