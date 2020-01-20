#include <std.h>
inherit OBJECT;

void init() {
	::init();
	add_action("read_history", "read");
}

void create() {
	::create();
	set_name("book");
	set_id( ({"book", "history book"}) );
	set_short("a history book of Kuril");
	set_long("Hand fashioned, this small book is actually a collection "
		"of excepts from the Diary of Lady Tiviel.  Very few of her "
		"writings remained after the Time of Flight.  This historical "
		"perspective has been reconstructed to shed light upon the "
		"history of Kuril.  In order to read it use the command: "
		"'read kuril history book'."
	);
	set_weight(30);
	set_value(50);
}

int read_history(string str) {
	if(!str) { return 0; }
	if(str == "kuril history book") {
		this_player()->more("/wizards/nevin/kuril/history/book_history");
	return 1;
	}
}
