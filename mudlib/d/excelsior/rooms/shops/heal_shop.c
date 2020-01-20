// /wizards/excelsior/rooms/shops/heal_shop

inherit "std/room";

void init() {
	::init();
	add_action("read","read");
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",1);
	set("short","In the grocery market");
	set("long","You are in a grocery market. Here various food products are "+
		"sold for your convenience. There is a sign on the counter.");
	set_items( (["counter":"It is a good counter.",
		 ({"sign","menu"}):"Read the sign to discover the menu of this wonderful place." ]) );
	set_exits( ([ "southeast":"/wizards/excelsior/rooms/street2",
		]) );
	reset();
}


int read( string str ) {
	object ob;
	ob = new("/wizards/excelsior/rooms/shops/cleric");
	write(
"The menu reads:\n"+
"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
"A glass of vodka          "+(int)ob->get_price("vodka")+"\n"+
"A glass of fine wine      "+(int)ob->get_price("wine")+"\n"+
"A cup of coffee           "+(int)ob->get_price("coffee")+"\n"+
"A bag of apples           "+(int)ob->get_price("bag of apples")+"\n"+
"A leg of lamb             "+(int)ob->get_price("a leg of lamb")+"\n"+
"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
"All prices are in gold.\n"+
"Simply 'buy <item>' to make a purchase.\n"+
"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	ob->remove();
	return 1;
}

void reset() {
	::reset();
	if(!present("cleric"))
		new("/wizards/excelsior/rooms/shops/cleric")->move(this_object());
}
