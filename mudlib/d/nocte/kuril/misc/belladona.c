#include <std.h>
inherit OBJECT;

void create() {
	::create();
	set_name("sprig of belladona");
	set_id( ({"sprig", "belladona", "sprig of belladona"}) );
	set_short("sprig of belladona");
	set_long(
		"A small sprig of belladona."
	);
	set_weight(1);
	set_value(15);
}
