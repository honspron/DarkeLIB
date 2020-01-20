#include <std.h>
#include <nevin.h>
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
   	set_name("gamorl");
    	set_id( ({ "merchant", "gamorl"}) );
    	set_short("Gamorl, the merchant");
   	set("aggressive", 0);
  	set_level(10);
    	set_long(
		"The merchant gestures for you to come and look at his goods."
	);
   	set_gender("male");
   	set("race", "dwarf");
	set_languages( ({"common", "dwarvish"}) );
   	add_money("silver", 100 + random(100));
    	set_body_type("human");
	set_emotes(1, ({
		"The merchant gestures for you to come and look at his goods.",
		"The merchant watches you carefully, worried that you've come "
			"to rob him.",
		"The merchant yells 'Fruits for sale!  Delicious fruits!'"
	}), 0);
	ob = new("/d/damned/virtual/battle-axe_4.weapon");
	ob->set_short("stout battle axe");
	ob->set_long("Designed for those shorter is statue, do not be fooled "
		"for this weapon's blade is very sharp.");
	ob->move(TO);
	force_me("wield battle axe in right hand");
	ob = new(ARM+"commoners_clothes");
	ob->set_short("fine clothes from a distant land");
	ob->set_long("Designed for the traveller in mind, these clothes "
		"are very sturdy");
	ob->move(TO);
	if(random(50) == 0) {
		ob = new(MAGIC+"wolf_orb");
		ob->move(TO);
	}
	force_me("wear clothes");
	set("storage room", MISC+"cart1");
	set("no sell", 1);
	set("markup", 30);
}

int chk_my_mob() {
	return 1;
}
