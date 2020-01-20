// /d/nfd/newbie/rooms/fr4.3

inherit "std/room";

void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/d/nfd/newbie/mon/elf_fighter");
		new("/d/nfd/newbie/weapons/spiked_long_sword")->move(mon);
		new("/d/nfd/newbie/armor/sweater")->move(mon);
		new("/d/nfd/newbie/armor/pants")->move(mon);
		new("/d/nfd/newbie/armor/shoes")->move(mon);
		mon->force_me("wear sweater");
		mon->force_me("wear pants");
		mon->force_me("wear shoes");
		mon->force_me("wield sword in right hand and left hand");
		mon->set_money("silver",70);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",1);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","In a desecrated section of the woods");
	set("long","The woods here seem to have been victim to some sort of "+
		"unnatural cataclysm. The beauty of the forest is not present here, "+
		"as no plant life seems to be alive. You walk among the dead old growths "+
		"and wonder what could have done such a thing.");
	set_smell("default","The dead plant life gives off pungant odors.");
	set_listen("default","You hear a brook to your north.");
	set_items((["woods":"They are destroyed here.",
		"brook":"It is too your north." ]));
	set_exits((["north":"/d/nfd/newbie/rooms/fr4.2",
		"southwest":"/d/nfd/newbie/rooms/fr3.4"]));
}
