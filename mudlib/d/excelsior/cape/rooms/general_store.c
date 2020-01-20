// /wizards/excelsior/cape/rooms/general_store.c

inherit "/std/vault";

void reset() {
	::reset();
	set_open("door",0);
	set_locked("door",1);
	"/wizards/excelsior/cape/storage/shop_store"->set_open("door",0);
	"/wizards/excelsior/cape/storage/shop_store"->set_locked("door",1);
	if(!present("shopkeeper")) {
		new("/wizards/excelsior/cape/mon/son")->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",1);
	set("short","Bob's General Store");
	set("long","This is one of the famous Bob's General Stores. Here, you "+
		"can sell what you don't want or no longer need, buy other peoples "+
		"items, or buy some new products. There is a shopkeeper here to help "+
		"you. There is a door leading north.");
	set_items((["store":"You are in it.",
		"products":"You can wheel and deal in them at this store.",
		"door":"It leads to the shop store room and is thus rightly secure."]));
	set_exits((["west":"/wizards/excelsior/cape/rooms/town3",
		"north":"/wizards/excelsior/cape/storage/shop_store"]));
	set_door("door","/wizards/excelsior/cape/storage/shop_store","north",
		"cape shop 1 key");
	set_lock_level("door",25);
	reset();
}

