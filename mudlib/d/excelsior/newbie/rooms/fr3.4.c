// /wizards/excelsior/newbie/rooms/fr3.4

inherit "std/room";

void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/wizards/excelsior/newbie/mon/elf");
		new("/wizards/excelsior/newbie/weapons/long_sword")->move(mon);
		new("/wizards/excelsior/newbie/armor/sweater")->move(mon);
		mon->force_me("wear sweater");
		mon->force_me("wield sword in right hand and left hand");
		mon->set_money("electrum",70);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","In a clearing");
	set("long","The woods part here opening up into a beautiful clearing. The "+
		"grass in this clearing is very green and the flowers are in bloom. "+
		"Little fury woodling creatures hop to and fro adding to your utter "+
		"enjoyment of this experience.");
	set_listen("default","You hear yourself singing from happiness.");
	set_smell("default","You smell fresh, clean, healthy air.");
	set_items((["woods":"They are ludicrously peaceful.",
		"creatures":"They are all fury and lovable."]));
	set_exits((["east":"/wizards/excelsior/newbie/rooms/fr4.4",
		"west":"/wizards/excelsior/newbie/rooms/fr2.4",
		"northeast":"/wizards/excelsior/newbie/rooms/fr4.3"]));
}
