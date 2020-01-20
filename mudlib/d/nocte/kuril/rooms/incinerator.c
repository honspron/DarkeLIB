#include <std.h>
#include "nevin.h"
inherit ROOM;

void init() {
	::init();
	add_action("save_me", "exit");
}

void reset() {
	object ob, *inv;
	int i;

	inv = all_inventory(this_object());
	i = sizeof(inv);
	while(i--) {
		inv[i]->remove();
	}
}
	
void create() {
	::create();
	set_property("indoors", 1);
	set_property("light", 2);
	set_property("night light", 2);
	set_property("no castle", 1);
	set_property("no attack", 1);
	set("short", "%^RED%^%^BOLD%^Nevin's Monster Incinerator%^RESET%^");
	set("long",
		"%^RED%^%^BOLD%^This is Nevin's Monster Incinerator room.  "
		"If you are a player you must leave immediately by typing "
		"'exit'.%^RESET%^");
}

int save_me(string str) {
	this_player()->move_player("/d/standard/square");
	return 1;
}
