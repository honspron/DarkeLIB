// /d/nfd/newbie/rooms/fr2.4

inherit "std/room";
void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/d/nfd/newbie/mon/elf");
		new("/d/nfd/newbie/weapons/spear")->move(mon);
		new("/d/nfd/newbie/armor/pants")->move(mon);
		mon->force_me("wear pants");
		mon->force_me("wield spear in right hand and left hand");
		mon->set_money("silver",52);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","Gamboling in the woods");
	set("long","You feel like gamboling in these peaceful and happy woods. "+
		"Everything seems cute and happy. No, not gambling. GambOling.");
	set_listen("default","You hear yourself singing from happiness.");
	set_items((["woods":"They are ludicrously peaceful."
		]));
	set_exits((["north":"/d/nfd/newbie/rooms/fr2.3",
		"east":"/d/nfd/newbie/rooms/fr3.4"]));
}
