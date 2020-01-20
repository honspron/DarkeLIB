// /wizards/excelsior/weapons/toaster

#include <std.h>

inherit WEAPON;

void create() {
	::create();
	set_name("mikey");
	set("id",({"mikey","rock"}) );
	set("short","Mikey, the incredible wieldable rock");
	set("long","This is a rather heavy rock with a label on it that says "+
		"'rock'. Being as you have no idea what "+
		"a rock is used for you just deside to use it as a weapon.");
	set_weight( 220 );
	set_value( 670 );
	set_ac( 2 );
	set_wc(8, "crushing");
	set_type("blunt");
	set_quality(4);
}
