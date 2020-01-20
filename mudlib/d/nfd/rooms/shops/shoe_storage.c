// /d/nfd/rooms/shops/shoe_storage

inherit "/std/room";

void reset() {
	int i;
	::reset();
	if(!present("iron boots"))
		new("/d/nfd/armor/iron_boots")->move(this_object());
	if(!present("leather-boots"))
		new("/d/damned/virtual/leather-boots.armour")->move(this_object());
	i = 2;
	while(i < 4) {
		if(!present("leather-boots "+i))
			new("/d/damned/virtual/leather-boots.armour")->move(this_object());
		i++;
	}
}

void create() {
	::create();
	set_property("light",-5);
	set("short","go away");
	set("long","go away");
	set_property("storage room",1);
	new("/d/nfd/armor/laen_boots")->move(this_object());
	reset();
}
