// /wizards/excelsior/obj/pen
// Excelsior 7-2-96

inherit "/std/Object";

void create() {
	::create();
	set_name("pen");
	set("id",({"feather pen","pen"}));
	set("short","A feather pen");
	set("long","This is a nice feather pen that can be used to write with.");
	set_weight(20);
	set_value(1);
}

void init() {
	::init();
	add_action("write","write");
}

int write(string str) {
	if(!str) {
		notify_fail("Write what?\n");
		return 0;
	}
	write("You write "+str+" on a nearby smooth surface.");
	message("other_action",(string)this_player()->query_cap_name()+" writes "+
		str+" on a nearby flat surface.",environment(this_player()),({this_player()}));
	return 1;
}
