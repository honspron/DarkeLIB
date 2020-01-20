// /wizards/excelsior/tinker/scale
// Excelsior 7-5-96

inherit "/std/Object";

void init() {
	::init();
	add_action("weigh","weigh");
}

void create() {
	::create();
	set_name("balance");
	set("id",({"scale","weight thing","balance"}));
	set("short","A balance");
	set("long","This device is useful in that you can use it to 'weigh' "+
		"an object. The device measures mass in the unit known as "+
		"'pebels'.");
	set_weight(80);
	set_value(100);
}

int weigh(string str) {
	object ob;
	if(!str) {
		notify_fail("What do you want to weigh?");
		return 0;
	}
	ob = present(str,this_player());
	if(!ob) {
		notify_fail("You can only weigh things in your inventory.\n");
		return 0;
	}
	message("other_action",(string)this_player()->query_cap_name()+
		" fiddles with a balance.",environment(this_player()),
		({this_player()}));
	write("After much hassle you figure the weight of the "+str+" to "+
		"be "+(int)ob->query_weight()+" pebels.");
	return 1;
}
