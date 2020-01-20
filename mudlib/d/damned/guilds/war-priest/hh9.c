// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// War-Priest Guild Hall
// 10/05/96

#include <std.h>

inherit "/std/vault";

void init() {
	::init();
	add_action("sit_chair", "sit");
	add_action("sing_song", "sing");
}

void create() {	
	object ob;
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("no castle", 1);
	set("short", "Hall of the Honoured");
	set("long",
		"Long wooden tables and study chairs fill the festhall.  "
		"It is here that the Priests of K'thach come to share "
		"song, tale, and camaradiere.  Ancient weapons and battle "
		"standards from age past cover the walls."
	);
	set_items( ([
		"tables": "They are very long and span the length of the room.",
		"chairs": "There are plenty for everyone.",
		"festhall": "It is a joyous place.  You gaze in respect "
			"upon the weapons and standards of the priests before "
			"you.",
		"weapons": "Swords, hammers, axes, and many more.  Each hangs "
			"next to a battle standard.",
		({"standard", "battle"}): "They are the battle standards "
			"of heroes who have long since past on.  Their names "
			"and deeds are sung nightly within this hall."
	]) );
	set_exits( ([
		"north": "/d/damned/guilds/war-priest/hh6",
//		"west": "/d/damned/guilds/war-priest/hh8"
	]) );
	set_door("wooden door", "/d/damned/guilds/war-priest/hh6", "north", 0);
	set_open("door", 1);
	set_locked("door", 0);
//	set_door("wooden door", "/d/damned/guilds/war-priest/hh8", "west", 0);
//	set_open("door", 1);
//	set_locked("door", 0);
	ob = new("/std/bboard");
	ob->set_name("board");
	ob->set_id( ({ "board", "war-priest_board" }) );
	ob->set_board_id("war-priest_board");
	ob->set_max_posts(25);
	ob->set_location("/d/damned/guilds/war-priest/hh9");
	ob->set("short", "Priests of K'thach Board");
	ob->set("long", "Board for the Priests of K'thach.");
}

int sit_chair(string str) {
	if(!str) { return 0; }
	if((str == "chair") || (str == "on chair")) {
		message("info", "You sit down upon a chair.", TP);
		message("info", TPQCN+" sits down upon a chair.", ENV(TP),
			({TP}) );
		return 1;
	}
}

int sing_song(string str) {
	string gender;
	if(!str || (str == "song")) {
		switch(random(2)) {
			case 0: gender = "heroes"; break;
			case 1: gender = "heroines"; break;
		}
		message("info", "You sing a song of "+gender+" past.", TP);
		message("info", TPQCN+" sings a song of "+gender+" past.", 
			ENV(TP), ({TP}) );
		return 1;
	}
}
