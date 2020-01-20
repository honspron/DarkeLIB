// /d/nfd/newbie/rooms/fr3.2

inherit "std/room";

void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/d/nfd/newbie/mon/elf");
		mon->set_level(2);
		new("/d/nfd/newbie/weapons/short_sword")->move(mon);
		new("/d/nfd/newbie/armor/pants")->move(mon);
		new("/d/nfd/newbie/armor/sweater")->move(mon);
		mon->force_me("wear sweater");
		mon->force_me("wear pants");
		mon->force_me("wield sword in right hand");
		mon->set_money("electrum",90);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","The woods continue");
	set("long","The woods continue here. To your east you can make out a small brook "+
		"running through the wilderness. You get the feeling something is wrong in "+
		"that direction...");
	set_listen("default","You hear a brook to the east.");
	set_items(([({"woods","wilderness"}):"They are ludocrously peaceful.",
		"brook":"It is to the east."]));
	set_exits((["east":"/d/nfd/newbie/rooms/fr4.2",
		"west":"/d/nfd/newbie/rooms/fr2.2",
		"northwest":"/d/nfd/newbie/rooms/fr2.1",
		"southwest":"/d/nfd/newbie/rooms/fr2.3"]));
}
