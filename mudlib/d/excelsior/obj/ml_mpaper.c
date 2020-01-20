// /wizards/excelsior/rooms/ml_mpaper

#include <std.h>

inherit OBJECT;

string query_song();
string query_notes();

void create() {
	::create();
	set_property("music paper",1);
	set_name("paper");
	set("id",({"paper","music paper","mary had a little lamb"}));
	set("short","A piece of music paper");
	set("long","This is a music paper with a title of 'Mary Had a Little Lamb'. "+
		"If only you knew how to read music.");
	set_weight(6);
	set_value(2);
}

string query_song() { return "Mary Had a Little Lamb"; }

string query_notes() { return "e d c d e e e d d d e g g"; }
