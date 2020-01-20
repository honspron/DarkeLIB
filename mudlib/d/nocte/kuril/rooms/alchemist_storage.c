#include <std.h>
#include "nevin.h"
inherit "std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", -3);
	set("short", "Alchemist Shop Storage Room");
	set("long",
		"Alchemical goods litter the floor and shelves.  Oops!  "
		"Watch out for that...doh!  And the...ouch!  You better "
		"leave before you hurt yourself.  A rune inscripted door "
		"to the west leads to the alchemist shop."
	);
	set_exits( ([
		"west": ROOMS+"alchemist"
	]) );
	set_items( ([
		"goods": "Wham!  Smash!  *SHATTER*  You aren't doing "
			"very well in here are you?",
		({"rune door", "rune inscripted door", "inscripted door"}):
			(: call_other, this_object(), "look_rune_door" :),
		"door": (: call_other, this_object(), "look_rune_door" :)
	]) );
	set_door("rune inscripted door", ROOMS+"alchemist",
		 "west", "kuril alchemist storage key");
	set_open("rune inscripted door", 0);
	set_locked("rune inscripted door", 1);
	set_lock_level("rune inscripted door", 50);
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
	for(i=1; i<=10; i++) {
		new(MISC+"jar")->
			move(this_object());
		new(MISC+"flask")->
			move(this_object());
		new(MISC+"beaker")->
			move(this_object());
		new(MISC+"belladona")->
			move(this_object());
		new(MISC+"adders_tongue")->
			move(this_object());
		new(MISC+"hemlock")->
			move(this_object());
		new(MISC+"ivy_leaf")->
			move(this_object());
		new(MISC+"petals")->
			move(this_object());
	}
	return;
}

void look_rune_door() {
	if(query_open("rune inscripted door")) {
		write("The rune inscripted door is open for your passage "
			"into the shop.");
	}
	else {
		write("The runed inscripted door is closed, barring your "
			"way.");
	}
}
