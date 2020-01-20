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
   	set_name("noleta");
    	set_id( ({ "merchant", "noleta" }) );
    	set_short("Noleta, the merchant");
   	set("aggressive", 0);
  	set_level(10);
    	set_long(
		"The merchant gestures for you to come and look at her goods."
	);
   	set_gender("female");
   	set("race", "high-man");
	set_languages("common");
   	add_money("silver", 100);
    	set_body_type("human");
	set_emotes(1, ({
		"The merchant shows off his fine fabrics which are for sale",
		"The merchant yells 'Fabrics!  The finest fabrics in all "
			"Kuril!'"
	}), 0);
	ob = new("/d/damned/virtual/short-sword_6.weapon");
	ob->move(TO);
	ob = new(ARM+"commoners_clothes");
	ob->set_short("scruffed up clothes");
	ob->set_long("Having seen too many days on the road and on the body of "
		"it's previous owner, these clothes are old and worn thin.");
	ob->set_value(30);
	ob->move(TO);
	force_me("wear clothes");
	set("storage room", MISC+"cart2");
	set("no sell", 1);
	set("markup", 40);
}

int chk_my_mob() {
	return 1;
}
