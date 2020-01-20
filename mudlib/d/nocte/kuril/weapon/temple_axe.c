// Coder: %^GREEN%^nEv!N%^RESET
// Darkemud
#include "nevin.h"
inherit "/std/weapon";

create() {
	string LONG;
	LONG = "Forged from a silvery alloy, this deadly weapon can "
		"chop through undead with ease.";
	::create();
	set("id", ({"axe", "battle axe", "silver battle axe"}) );
	set("short", "wickedly sharp battle axe");
	set_weight(200);
	set_wc(12, "cutting");
	if(random(50) == 0) {
		set_wc(8, "disruption");
		set_long(LONG+"  Upon the blade are glyphs of chaos and "
			"destruction.");
		set_value(300);
		set_wield("Your arm quivers as you grab the axe for battle.");
	}
	else {
		set_long(LONG);
		set_value(100);
		set_wield("You grab the silvery battle axe for battle");
	}
	set_ac(5);
	set_type("axe");
	set_quality(5);
	set_parry_bonus(-15);
	set_material("silver");
}
