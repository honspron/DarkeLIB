// /d/nfd/newbie/rooms/fr2.2

inherit "std/room";
void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/d/nfd/newbie/mon/elf");
		new("/d/nfd/newbie/weapons/short_sword")->move(mon);
		new("/d/nfd/newbie/armor/shoes")->move(mon);
		mon->force_me("wear shoes");
		mon->force_me("wield sword in right hand");
		mon->set_money("electrum",40);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","In the woods");
	set("long","The woods around you are very serene and beautiful. You "+
		"could stay here forever. You feel like singing. Lalalalalala!");
	set_listen("default","You hear your self singing from happiness.");
	set_items((["woods":"They are ludocrously peaceful."
		]));
	set_exits((["east":"/d/nfd/newbie/rooms/fr3.2",
		"west":"/d/nfd/newbie/rooms/fr1.2"]));
}
