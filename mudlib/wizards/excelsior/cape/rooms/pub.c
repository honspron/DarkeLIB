#include "/wizards/excelsior/misc/domain.h"

// /wizards/excelsior/cape/rooms/heal_shop

inherit "std/room";

void init() {
	::init();
	add_action("read","read");
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",1);
	set("short","In the South Cape Tavern");
	set("long","For being the quiet and peaceful town that it is, South Cape "+
		"has quite a tavern. This is where all the towns folk come and let out "+
		"all the aggression that builds up while living in a quiet and peaceful "+
		"town. It is said that there is never less than 3 seperate brawls going "+
		"on in the tavern at any given time. There is a sign on the counter.");
	set_items( (["tavern":"Quite the rowdy crowd here.",
		"sign":"Read the sign to discover that it's a menu.",
		"brawls":(:call_other, this_object(), "brawls" :),
		"folks":"The folks here are very folksy indeed.",
		"town":"It is quite and peaceful."]) );
	set_exits( ([ "north":"/wizards/excelsior/cape/rooms/town2",
		]) );
}


int read( string str ) {
	object ob;
	ob = new("/wizards/excelsior/cape/mon/barkeep");
	write(
"The menu reads:\n"+
"%^RED%^=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
"%^RESET%^"+
"A glass of vodka          "+(int)ob->get_price("vodka")+"\n"+
"A glass of fine wine      "+(int)ob->get_price("wine")+"\n"+
"Scotch on the rocks       "+(int)ob->get_price("scotch")+"\n"+
"A cup of coffee           "+(int)ob->get_price("coffee")+"\n"+
"A bag of apples           "+(int)ob->get_price("bag of apples")+"\n"+
"%^RED%^=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
"%^RESET%^"+
"All prices are in copper.\n"+
"Simply 'buy <item>' to make a purchase.\n"+
"%^RED%^=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	ob->remove();
	return 1;
}

void reset() {
	::reset();
	if(!present("barkeep"))
		new("/wizards/excelsior/cape/mon/barkeep")->move(this_object());
}

string brawls() {
	int i;
	i = random(4)+3;
	write("You count "+i+" brawls going on right now.");
	return "You count "+i+" brawls going on right now.";
}
