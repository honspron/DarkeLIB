#include <std.h>
#include <nevin.h>
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("night light", 0);
	set_property("no castle", 1);
	set("short", "Magic Shop Storage Room");
	set("long",
		""
	);
	set_exits( ([
		"east": "magic_shop"
	]) );
	set_items( ([
		({"rune covered door", "rune door", "rune"}): 
			(: this_object(), "look_door" :)
	]) );
	set_door("rune covered door", ROOMS+"magic_shop",
		 "east", "kuril magic shop storage key"); 
	set_open ("rune covered door", 0);
	set_locked("rune covered door", 1);
	set_lock_level("rune covered door", 25);
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
	for(i=1; i<=3;i++) {
		new(MAGIC+"wolf_orb")->move(TO);
		new(MAGIC+"brownie_orb")->move(TO);
		new(MAGIC+"dire_wolf_orb")->move(TO);
		if(i == 1) { new(MAGIC+"minotaur_orb")->move(TO); }
	}
	return;
}

void look_door() {
	if(query_open("rune covered door")) {
		write("The rune covered door is open.");
	}
	else {
		write("The rune covered door is closed.");
	}
}
