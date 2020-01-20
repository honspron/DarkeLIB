// /wizards/excelsior/obj/paint_brush

inherit "/std/Object";

void create() {
	::create();
	set_name("brush");
	set("id",({"paint brush","brush","not a tooth brush"}));
	set("short","paint brush");
	set("long","This is a paint brush. With it, you can 'paint <thing>'");
	set_weight(30);
	set_float_value(0.2);
}

void init() {
	::init();
	add_action("paint","paint");
}

int paint(string str) {
	string name;
	name = (string)this_player()->query_cap_name();
	if(!str) {
		message("my_action","You paint a self portrait of yourself on the ground. "+
			"You are sooooo beautiful!",this_player());
		message("other_action",name+" paints a self portrait on the ground. "+
			"The damn vandal!",environment(this_player()),({this_player()}));
		return 1;
	}
	if(find_player(str)) {
		message("my_action","You paint a portrait of "+capitalize(str)+" on a wall. "+
			"Your talents soar!",this_player());
		message("other_action",name+" paints an unflattering picture of "+
		capitalize(str)+" on a wall. Who does "+(string)this_player()->query_subjective()+
		" think "+(string)this_player()->query_subjective()+" is!",
			environment(this_player()),({this_player()}));
		return 1;
	}
	message("my_action","You paint a picture of a "+str+" on a wall. "+
			"You are a regular van Gough!",this_player());
		message("other_action",name+" paints a  picture of a "+
		str+" on a wall. If "+(string)this_player()->query_subjective()+
		" hadn't told you you could never have told that's what it is.",
			environment(this_player()),({this_player()}));
	return 1;
}


int is_right_brush() { return 1; }
