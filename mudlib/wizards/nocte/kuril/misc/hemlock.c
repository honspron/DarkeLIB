#include <std.h>
inherit OBJECT;

void create() {
	::create();
	set_name("sprig of hemlock");
	set_id( ({"sprig", "hemlock", "sprig of hemlock"}) );
	set_short("sprig of hemlock");
	set_long(
		"A small sprig of hemlock."
	);
	set_weight(1);
	set_value(23);
}
