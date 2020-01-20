#include <std.h>

inherit OBJECT;

void init() {
	::init();
	add_action("look_arch", "look");
}

void create() {
	::create();
	set_name("arch");
	set_id( ({"arch", "archway"}) );
	set_short("%^WHITE%^%^BOLD%^A graceful arch%^MAGENTA%^%^BOLD%^");
	set_long("Upon closer inspection you notice that something "
		"has been removed from the arch.  Fist sized holes "
		"gape at you from the top of the arch like an eyeless "
		"socket."
	);
	set_weight(100000);
	set_value(0);
}

int look_arch(string str) {
	if(!str) {
		return 0;
	}
	if((str == "designs") || (str == "carvings")) {
		write("Somehow, this archway has withstood the passage of "
			"time almost perfectly.");
		return 1;
	}
}

int clean_up() { return 0; }
