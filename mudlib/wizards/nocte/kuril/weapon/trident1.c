// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <nevin.h>
#define	WC1	17	// impaling
#define	WEIGHT	250
#define	VALUE	150
#define AC	4
#define PARRY	-15
#define VERB	"pierce"
#define QUALITY	5
inherit "/std/weapon";

create() {
	::create();
	set("short", "black bladed trident");
	set("long",
		"With the ears and other body parts impaled upon the "
		"prongs, this trident is truely a deadly weapon."
	);
	set_wield("You grasp the trident in preparation for battle.");
	set_wc(WC1, "impaling");
	set_type("two handed polearm");
	set("id", ({"trident", "black trident"}) );
	set_weight(WEIGHT);
	set_value(VALUE);
	set_ac(AC);
	set_parry_bonus(PARRY);
	set_verb(VERB);
	set_quality(QUALITY);
}
