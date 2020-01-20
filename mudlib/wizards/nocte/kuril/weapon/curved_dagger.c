// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <nevin.h>
#define	WC1	5	// impaling
#define WC2	9	// cutting
#define	WEIGHT	45
#define	VALUE	100	
#define AC	3
#define PARRY	4
#define VERB	"slice"
#define QUALITY	5
inherit "/std/weapon";

create() {
	::create();
	set("short", "curved bladed dagger");
	set("long",
		"This long curved bladed dagger is used primarily in the "
		"disection and dismemberment of various forms of life."
	);
	set_wc(WC1, "impaling");
	set_wc(WC2, "cutting");
	set_type("blade");
	set("id", ({"dagger", "curved dagger", "curved bladed dagger"}) );
	set_weight(WEIGHT);
	set_value(VALUE);
	set_ac(AC);
	set_parry_bonus(PARRY);
	set_verb(VERB);
	set_quality(QUALITY);
	set_material("/metal/iron");
	TO->set_decay_rate(TO->prop("hardness"));
}
