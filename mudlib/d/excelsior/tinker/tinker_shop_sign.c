// /wizards/excelsior/tinker/tinker_shop_sign

inherit "std/Object";

void create() {
	::create();
	set_property("no get",1);
	set_name("notice");
	set("id",({"policy notice","shop sign","tinker shop sign","sign","notice",
		"tinker shop notice","shop policy","policy","store policy",
		"tinker shop policy"}));
	set("short","a sign explaining the tinker shop policy");
	set("long","You will have to 'read' this wonderful sign to discover what "+
		"delightful information it contains.");
	set_weight(1000000);
	set_float_value(0.01);
}

void init() {
	::init();
	add_action("read_sign","read");
}

int read_sign(string str) {
	string open,join_room;
	if(!id(str)) return 0;
	join_room = "/d/damned/guilds/join_rooms/tinker_join";
	if((int)environment()->query_property("shop_open")) {
		open = "open"; } else {
		open = "closed"; }
	write("You peruse the sign.");
	write("The shop is currently %^GREEN%^"+open+" %^RESET%^to the general public.");
	write("-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-");
	this_player()->more("/wizards/excelsior/doc/tinker_shop_dir");
	write("-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-");
	if((int)environment()->query_property("shop_open")) {
		open = "open"; } else {
		open = "closed"; }
	return 1;
}
