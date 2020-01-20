// /wizards/excelsior/armor/orc_platemail
// this may turn out to be the best armor in my area

#include <std.h>

inherit ARMOUR;

void create() {
	::create();
	set_name("platemail");
	set("id", ({"platemail","modern platemail"}));
	set("short","Some fancy looking platemail armour");
	set("long","This armour looks like the kind of thing you see in your dreams it is so well crafted. "+
	
	"It is extremely intricate and convoluted in its "+
		"design, but looks as though it would protect its wearer quite well . It appears to be made out of laen. Wow.");
	set_material("/metal/laen");
	set_type("body armour");
	set_ac(10);
	set_limbs( ({"torso"}) );
	set_weight(320);
	set_value(1233);
}
