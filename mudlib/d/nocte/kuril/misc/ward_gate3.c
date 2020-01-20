#include <std.h>
#include "nevin.h"
inherit OBJECT;

void init() {
	::init();
	add_action("look_gate", "look");
}

void create() {
	::create();
	set_name("gate");
	set_id( ({"gate", "ward gate"}) );
	set_long(
		"Rusted and in disrepair, the ward gate serves to provide "
		"a buffer zone between the factions of the necromancers and "
		"the dark temple."
	);
	set_weight(100000);
	set_value(0);
}

string query_short() {
	if(call_other(ROOMS+"magus_lane4", "query_open",
		"ward gate")) { return "%^ORANGE%^%^BOLD%^an open ward gate%^MAGENTA%^%^BOLD%^"; }
	return "%^ORANGE%^%^BOLD%^a closed ward gate%^MAGENTA%^%^BOLD%^";
}

int look_gate(string str) {
	if(!str) { return 0; }
	if(!(str == "gate") || !(str == "ward gate")) { return 0; }
	write("Rusted and in disrepair, the ward gate serves to "
		"provide a buffer zone between the factions of the "
		"necromancers and the dark temple.");	
	return 1;
}

int clean_up() { return 0; }
