// /wizards/excelsior/weapons/bottle

#include <std.h>

inherit WEAPON;

void create() {
	::create();
	set("id",({"broken wine bottle","bottle","broken bottle"}));
	set("name","bottle");
	set("short","broken wine bottle");
	set("long","This is a broken bottle of wine. It could probably be used as some "+
		"sort of weapon.");
	set_weight(25);
	set("value",2);
	set_ac(1);
	set_wc(1,"cutting");
	set_type("blade");
	set_quality(1);
}
