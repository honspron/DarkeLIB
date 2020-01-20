// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Blackened Shield

#include <nevin.h>
inherit "/std/armour";

create() {
	::create();
	set("id", ({ "blackened shield", "shield", "small shield" }) );
	set_type("shield");
	set_limbs( ({ ({"right hand", "left hand", "first branch",
		"second branch", "third branch", "fourth branch", "first hand",
		"second hand", "third hand", "fourth hand" }) }) );
	set("short", "a blackened shield");
	set("long", 
		"Covered in a layer of dried blood, this shield has small "
		"spikes protruding from its surface."
	);
	set_weight(120);
	set_value(80);
	set_ac(22);
	set_ac(1, "aether");
	set_ac(1, "depression");
	set_ac(5, "acid");
	set_ac(1, "vacuum");
	set_ac(10, "fire");
	set_ac(10, "cold");
	set_ac(22, "impact");
	set_ac(1, "stress");
	set_ac(10, "strike");
	set_ac(22, "cutting");
	set_ac(22, "impaling");
	set_ac(1, "electricity");
	set_ac(1, "time");
	set_ac(22, "crushing");
	set_ac(1, "disruption");
	set_ac(1, "holy");
	set_ac(10, "plasma");
	set_ac(1, "infernal");
	set_material("metal/mcgrail");
}
