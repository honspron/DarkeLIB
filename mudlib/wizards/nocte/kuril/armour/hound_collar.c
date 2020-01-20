// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit ARMOUR;

void create() {
	::create();
	set_name("collar");
	set("id", ({ "collar", "spiked collar" }) );
	set("short", "spiked collar");
	set("long",
		"Forged from chyrite, a form of primal chaos which does not "
		"exist naturally on this world, this collar shifts and "
		"bends about.  Forced into a semi-solid form by powerful "
		"magic, this collar weighs almost nothing.  This particular "
		"collar is used to tame chaos hounds for service to the "
		"Order."
	);
	set_material("chyrite");
	set_type("neck");
	set_ac(5);
	set_weight(5);
	set_value(0);
}
