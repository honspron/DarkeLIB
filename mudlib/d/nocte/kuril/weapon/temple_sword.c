// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include "nevin.h"
#define	WC1	4	// impaling
#define WC2	9	// cutting
#define	WEIGHT	55
#define	VALUE	100
#define AC	3
#define PARRY	7
#define VERB	"slice"
#define QUALITY	5
inherit "/std/weapon";

create() {
	::create();
	set("short", "curved bladed short sword");
	set("long",
		"Fashioned from a high quality silver alloy, this blade "
		"is the bane of undead.  It cleaves through the undead "
		"with ease."
	);
	set_wield("You grab the sword for battle.");
	set_wc(WC1, "impaling");
	set_wc(WC2, "cutting");
	set_type("blade");
	set("id", ({"sword", "short sword"}) );
	set_weight(WEIGHT);
	set_value(VALUE);
	set_ac(AC);
	set_parry_bonus(PARRY);
	set_verb(VERB);
	set_quality(QUALITY);
	set_material("silver");
}
