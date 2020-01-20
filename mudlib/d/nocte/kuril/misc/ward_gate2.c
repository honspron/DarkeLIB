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
	set_weight(100000);
	set_value(0);
}

string query_short() {
	if(call_other(ROOMS+"fountain_square4", "query_open",
		"ward gate")) { return "%^ORANGE%^%^BOLD%^an open ward gate%^MAGENTA%^%^BOLD%^"; }
	return "%^ORANGE%^%^BOLD%^a closed ward gate%^MAGENTA%^%^BOLD%^";
}

int look_gate(string str) {
	if(!str) { return 0; }
	if((str == "gate") || (str == "ward gate")) {
	string STR;
	STR = "Rusted and in disrepair, the ward gate serves to protect "
		"the nobles from the filth of the Lower Ward.";
	if(call_other(ROOMS+"fountain_square", 
		"check_sentry")) {
		STR = STR + "  On the other side you can see gate sentries "
			"keeping vigilent watch.";
	}
	write(STR);
	return 1;
	}
}

int clean_up() { return 0; }
