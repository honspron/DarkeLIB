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
   	set_name("isymaivenonythe");
    	set_id( ({ "merchant", "isymaivenonythe" }) );
    	set_short("Isymaivenonythe, the merchant");
   	set("aggressive", 0);
  	set_level(10);
    	set_long(
		"The merchant gestures for you to come and look at his goods."
	);
   	set_gender("male");
   	set("race", "gnome");
	set_languages( ({"common", "grken"}) );
   	add_money("silver", 100);
    	set_body_type("human");
	set_emotes(1, ({
		"A merchant yells 'Get ya daggahs har!  Daggahs for sale!'"
	}), 0);
	ob = new("/d/damned/virtual/dagger_6.weapon");
	ob->move(TO);
	force_me("wield dagger in left hand");
	ob = new(ARM+"commoners_clothes");
	ob->set_short("filthy clothes");
	ob->set_long("Filthy clothes that have seen too many days and nights "
		"upon the same unwashed body.");
	ob->move(TO);
	force_me("wear clothes");
	set("storage room", MISC+"cart4");
	set("no sell", 1);
	set("markup", 35);
}

int chk_my_mob() {
	return 1;
}
