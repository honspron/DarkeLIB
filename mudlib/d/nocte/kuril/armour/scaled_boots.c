// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Scaled Boots
// 10/15/96

#include "nevin.h"
inherit "/std/armour";

create() {
	::create();
	set_name("scaled leather boots");
	set("id", ({ "boots", "scaled boots", "scaled leather boots" }) );
	set_type("boots");
	set_limbs( ({ "left foot", "right foot" }) );
	set("short", "scaled leather boots");
	set("long", 
		"Fashioned from the scaled skin of some type of large "
		"reptile, these boots are both sturdy and very protective."
	);
	set_weight(80);
	set_value(200);
	set_ac(12);
	set_ac(1, "aether");
	set_ac(1, "depression");
	set_ac(10, "acid");
	set_ac(6, "vacuum");
	set_ac(10, "fire");
	set_ac(10, "cold");
	set_ac(3, "impact");
	set_ac(1, "stress");
	set_ac(2, "strike");
	set_ac(12, "cutting");
	set_ac(12, "impaling");
	set_ac(5, "electricity");
	set_ac(1, "time");
	set_ac(8, "crushing");
	set_ac(1, "disruption");
	set_ac(1, "holy");
	set_ac(1, "plasma");
	set_ac(1, "infernal");
	set_material("leather");
}
