// /wizards/excelsior/newbie/rooms/fr4.4

inherit "std/room";

void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/wizards/excelsior/newbie/mon/elf");
	mon->set_level(3);
		new("/wizards/excelsior/newbie/weapons/spear")->move(mon);
		new("/wizards/excelsior/newbie/armor/sweater")->move(mon);
		new("/wizards/excelsior/newbie/armor/pants")->move(mon);
		mon->force_me("wear sweater");
		mon->force_me("wear pants");
		mon->force_me("wield spear in right hand and left hand");
		mon->set_money("electrum",70);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",1);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","In a darker part of the woods");
	set("long","The woods here get a little darker, but you are so brave it "+
		"barely even scares you. My aren't you brave! To the south you observe "+
		"a small house of some sort. It looks very cozy. There is smoke rising "+
		"peacefully from a chimney on the house's roof.");
	set_smell("default","You smell wood burning to the south.");
	set_listen("default","You hear a brook to your north.");
	set_items((["woods":"They are a little darker here.",
		"house":"It looks very cozy and pleasant.",
		"chimney":"It is made out of red bricks",
		"smoke":"It is the nice kind of smoke." ]));
	set_exits((["west":"/wizards/excelsior/newbie/rooms/fr3.4",
		"south":"/wizards/excelsior/newbie/rooms/fr4.5"]));
}
