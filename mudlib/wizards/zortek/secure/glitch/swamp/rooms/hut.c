//	Wizard:	Glitch
//	Hut
//	hut.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 3);
	set_property("indoors", 1);
	set("short", "hut");
	set("long", "You find yourself inside a primitive hut.  Very simple "+
		"furniture is scattered about the room.  In the center of the "+
		"hut, a small fire burns.");
	add_exit("sw25","out");
	set_items(([ "hut" : "A very primitive, though functional hut.",
		({ "furniture" }) : "A crude table and chair, also a small "+
		"cot.",
		({ "table","chair" }) : "Very crude funishings.",
		({ "cot" }) : "A rude cot, though functional like everything "+
		"else in the hut.",
		({ "fire" }) : "A small, though hot fire."]));
	set_smell("default", "THe armoma of unwashed bodies, fetid swamp and "+
		"wood smoke combine into one heck of a stench.");
	set_listen("default","You hear the sounds of the fire crackling.");
}

void reset() {
	::reset();
	if(!present("hermit", this_object()) ) {
		new("/wizards/glitch/swamp/mons/hermit")->move(this_object());
	}
}
