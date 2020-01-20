// /wizards/excelsior/obj/jail_keys
// a set of keys that opens everything in the jail

#include <std.h>

inherit OBJECT;

void create() {
	::create();
	set_name("keys");
	set("id",({"jail keys","key","keys","set of keys","set of jail keys"}));
	set("short","A set of jail keys");
	set("long","This is a set of jail keys that, judgin by the large number "+
		"of keys on the ring, should be able to unlock a large number of doors.");
	set_weight(15);
	set_value(1);
}
