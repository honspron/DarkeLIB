#include <std.h>
inherit OBJECT;

void create() {
	::create();
	set_name("poison ivy leaf");
	set_id( ({"leaf", "ivy", "poison ivy", "poison ivy leaf"}) );
	set_short("poison ivy leaf");
	set_long(
		"A leaf of poison ivy."
	);
	set_weight(1);
	set_value(3);
}
