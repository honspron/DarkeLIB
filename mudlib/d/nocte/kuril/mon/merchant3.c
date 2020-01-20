#include <std.h>
#include "nevin.h"
inherit "/std/npc_shop";

void init() {
	::init();
	if(query_night()) {
		if(!wizardp(this_player())) {
			 this_object()->move_object(ROOMS+"incinerator");
		}
	}
}

create() {
	object ob;
    	::create();
   	set_name("v'nebree");
    	set_id( ({ "merchant", "v'nebree"}) );
    	set_short("V'nebree, the merchant");
   	set("aggressive", 0);
  	set_level(10);
    	set_long(
		"The merchant gestures for you to come and look at his goods."
	);
   	set_gender("male");
   	set("race", "high-man");
	set_languages("common");
   	add_money("silver", 100);
    	set_body_type("human");
	set_emotes(1, ({
		"The merchant shouts, 'Carpets from the around the world!  "
			"Get your carpets here!'",
		"The merchant shouts, 'Carpets fit for a king!  Large enough "
			"for any size harem!  Carpets!'"
	}), 0);
	ob = new("/d/damned/virtual/scimitar_4.weapon");
ob->set_wc(32, "fire");
	ob->set_property("flame blade", 4);
	ob->set_decay_rate(50);
	ob->move(TO);
	force_me("wield scimitar in right hand");
	ob = new(ARM+"commoners_clothes");
	ob->set_short("fine clothes from a distant land");
	ob->set_long("Designed for the traveller, these clothes have been "
		"worn for a long time.");
	ob->move(TO);
	force_me("wear clothes");
	set("storage room", MISC+"cart3");
	set("no sell", 1);
	set("markup", 25);
}

int chk_my_mob() {
	return 1;
}
