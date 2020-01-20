#include <std.h>
inherit OBJECT;

void create() {
	::create();
	set_name("bridge");
	set_id( ({"bridge", "burnt bridge"}) );
	set_short("%^BLUE%^%^BOLD%^A burnt, collapsed bridge%^MAGENTA%^%^BOLD%^");
	set_long(
		"Once spanning the river below, it is now just a charred "
		"skeleton of a bridge."
	);
	set_weight(100000);
	set_value(0);
}

int clean_up() { return 0; }
