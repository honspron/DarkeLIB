// /wizards/excelsior/weapons/flail_of_death
// a nasty little weapon for a little know skill

#include <std.h>

inherit WEAPON;

void create() {
	::create();
	set_name("flail");
	set("id",({"flail","flail of death","blue flail"}) );
	set("short","blue flail");
	set("long","This two handed flail is dark blue and made out of solid iron. "+
		"It would be quite "+
		"devastating in the hands of someone who knew how to use it.");
	set_weight(220);
	set_value(531);
	set_ac(2);
	set_wc(18,"cutting");
	set_type("two handed flail");
	set_quality(5);
}
