//	Wizard:  Glitch
//	Trolltown
//	c_hut.c

#include <std.h>

inherit ROOM;

int search_count;

void create() {
	::create();
	search_count=0;
	set_property("light", 3);
	set_property("indoors", 1);
	set("short", "Hut");
	set("long", "You're in a fairly well built hut.  Good quality furs "+
	"cover the floor.  A fire burns in a small fire pit in one corner. "+
	"Fair quality furnishing fill the rest of the room.");
	add_exit("tt13","south");
	set_items(([
	"fire" : "A small fire burns in the fire pit.",
	({ "pit","fire pit"}) : "A shallow hole in the floor, a fire "+
	"burns in it.",
	({ "fur","furs" }) : "Decent quality furs, though not very valuable.",
	({ "furnishing" }) : "The furnishings are of a good quality and "+
	"heavy construction."
]));
	set_smell("default", "You smell smoke.");
	set_listen("default","You hear a fire crackling.");
	set_search("default",(: this_object(),"do_search" :));
}

void do_search() {
	int skill;
	say(this_player()->query_cap_name()+" appears to be searching "+
	"the furs.\n");
	skill=(int)this_player()->query_skill("perception");
	if((random(100)>skill) && search_count<3) {
		search_count++;
		write("Your search is successful.");
		add_exit("hole","hole");
	}
	else
		write("Your search yeilds nothing.");
	return;
}

void reset() {
	::reset();
	if(!present("chief", this_object()) ) {
		new("/wizards/glitch/swamp/mons/chief")->move(this_object());
	}
}
