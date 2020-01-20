// /wizards/excelsior/obj/mystic_compass
// Excelsior 7-3-96

inherit "/std/Object";

void create() {
	::create();
	set_name("compass");
	set("id",({"compass","mystic compass"}));
	set("short","A mystic compass");
	set("long","This object uses lunar and solar alignments to help "+
		"you calculate your exact position on the island. When on "+
		"the island of the damned, you can 'locate' yourself.");
	set_weight(90);
	set_value(700);
}

void init() {
	::init();
	add_action("locate","locate");
}

int locate(string str) {
	int x,y;
	string file;
	if(str) return 0;
	file = file_name(environment(this_player()));
	if(sscanf(file,"/d/damned/virtual/room_%d_%d.world",x,y) != 2) {
		write("You have to be on the island to use the compass.");
		return 1;
	}
	if((int)this_player()->query_stats("intelligence") < 70) {
		write("You are not smart enough to use the mystic compass!! Doh!!");
		return 1;
	}
	write("You use your compass and calculate you position to be "+
		"roughly "+x+", "+y+".");
	message("other_action",(string)this_player()->query_cap_name()+" fiddles "+
		"with a compass.",environment(this_player()),({this_player()}));
	return 1;
}
