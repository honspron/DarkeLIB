// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Modified from Khojem's ravine code

#include <std.h>
#include "nevin.h"
inherit ROOM;

void init() {
	::init();
	add_action("fly_up", "up");
	if(TP->chk_my_mob()) { add_action("no_exit", "south"); }
}

void reset() {
	::reset();
	if(!present("zombie")) {
		new(MON+"ku_zombie")->move(TO);
		new(MON+"ku_zombie")->move(TO);
		new(MON+"ku_zombie")->move(TO);
	}
	if(!present("wight")) {
		new(MON+"ku_wight2")->move(TO);
	}
}

void create() {
	::create();
	set_property("light", 1);
	set_property("night light", -3);
	set_property("indoors", 0);
	set("short", "A runed covered tube");
	set("long",
		"You are at the bottom of the long tube.  To the south you "
		"can see a large river flowing past you.  Water, up to your "
		"knees, fills the small grotto.  Metal structures lie rusting "
		"about you.  Looking out onto the rapidly flowing river you "
		"wonder what these tubes where used for."
	);
	set_items( ([
		"runes": (: call_other, this_object(), "look_rune" :),
		"tube": "It is right above you, how you are going to get "
			"back up there you have no idea.",
		"river": "It is to the south, it's quickly moving waters "
			"flow into the ocean.",
		({"metal", "structures"}): "Now twisted and mangled, "
			"they could have once served as mooring posts for "
			"boats travelling along the river."
	]) );
	set_exits( ([
		"up": ROOMS+"stube2",
		"south": ROOMS+"r6"
	]) );
}

int fly_up() {
	if(!this_player()->query_flying()) {
		write("You try and flap your arms around but you just can not "
			"fly.");
		say(this_player()->query_cap_name() + " flaps " +
			this_player()->query_possessive() + " arms around "
			"but doesn't leave the ground.");
		return 1;
	}
	if(this_player()->query_flying()) {
		write("You fly up the tube.");
		tell_room(ROOMS+"stube2",
			this_player()->query_cap_name() + "flies up from " +
				"the depths below.");
	}
}

int no_exit() { return 1; }
