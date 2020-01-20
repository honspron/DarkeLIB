// /d/nfd/obj/emporium/dir_sign

#include <std.h>

inherit OBJECT;

void init() {
	::init();
	add_action("read","read");
}

void create() {
	::create();
	set_name("sign");
	set("id",({"sign","directions","arrow sign"}));
	set("short","A sign with arrows on it");
	set("long","This appears to be a sign directing you about this complex. Try "+
		"'read'ing it.");
	set_weight(200000);
	set_value(0);
}

int read(string str) {
	if(present(str) != this_object()) {
		notify_fail("Read what?\n");
		return 0;
	}
	write("You read the sign.");
	this_player()->more("/wizards/excelsior/doc/sign");
	return 1;
}
