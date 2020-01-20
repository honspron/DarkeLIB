#include <std.h>
#include <nevin.h>
inherit OBJECT;

void create() {
	::create();
	set_name("gate");
	set_id( ({"gate", "ward gate"}) );
	set_long(
		"Rusted and in disrepair, the ward gate serves to protect "
		"the nobles from the filth of the Lower Ward."
	);
	set_weight(100000);
	set_value(0);
}

string query_short() {
	if(call_other(ROOMS+"fountain_square", "query_open",
		"ward gate")) { return "%^ORANGE%^%^BOLD%^an open ward gate%^MAGENTA%^%^BOLD%^"; }
	return "%^ORANGE%^%^BOLD%^a closed ward gate%^MAGENTA%^%^BOLD%^";
}

int clean_up() { return 0; }
