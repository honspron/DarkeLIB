// /d/nfd/rooms/tt_mpaper



#include <std.h>



inherit OBJECT;



string query_song();

string query_notes();



void create() {

	::create();

	set_property("music paper",1);

	set_name("paper");

	set("id",({"paper","music paper","twinkle twinkle little star"}));

	set("short","A piece of music paper");

	set("long","This is a music paper with a title of 'Twinkle Twinkle "+	

		"Little star'. If only you knew how to read music.");

	set_weight(6);

	set_value(2);

}



string query_song() { return "twinkle twinkle little star"; }



string query_notes() { return "c c g g a a g"; }

