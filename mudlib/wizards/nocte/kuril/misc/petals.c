#include <std.h>
inherit OBJECT;

void create() {
	::create();
	set_name("rose petals");
	set_id( ({"petals", "rose petals"}) );
	set_short("rose petals");
	set_long(
		"A handful of rose petals."
	);
	set_weight(1);
	set_value(6);
}
