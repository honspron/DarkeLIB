// Coder: %^GREEN%^nEv!N%^RESET
// Darkemud
// shovel for digging about
// Usage: To use it, just code dig_room() in any room and the shovel will
// automatically call that function.
#include <std.h>
inherit "/std/weapon";

void init() {
	::init();
	add_action("hold_shovel", "hold");
	add_action("dig_around", "dig");
}

void create() {
	::create();
	set("name", "shovel");
	set("short", "a large shovel");
	set("long",
		"Used by farmers all over the world, this shovel is useful "
		"for digging around and for smashing those annoying mice "
		"that scurry about farms."
	);
	set_wield("You grab the shovel.");
	set_unwield("You release the shovel.");
	set_wc(8, "crushing");
	set_type("two handed polearm");
// First id must be "shovel" or dig_around() will not work
	set("id", ({"shovel"}) );
	set_weight(150);
	set_value(40);
	set_ac(3);
	set_parry_bonus(-20);
	set_verb("smash");
	set_quality(2);
	set_property("no add quality", 1);
	set_material("/metal/iron");
	TO->set_decay_rate(TO->prop("hardness"));
}

int hold_shovel(string str) {
	if(!str) { return 0; }
	if(str == "shovel") {
		message("info", "Just wield it", TP);
	}
}

int dig_around(string str) {
	object *inv;
	string *id;
	int i;
	if(!str){
		notify_fail("What are you trying to dig?");
return 0;
}
	inv = all_inventory(TP);
	i = sizeof(inv);
	if(str == "ground") {
		while(i--) {
			id = inv[i]->query_id();
			if(id[0] == "shovel") {
				call_other(ENV(TP), "dig_room"); 
				call_other(ENV(TP), "dig_corpse");
				return 1;
			}
		}
	}
}
