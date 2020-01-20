// /wizards/excelsior/newbie/rooms/fr4.3

inherit "std/room";

void reset() {
	object mon;
	::reset();
	if(!present("elf")) {
		mon = new("/wizards/excelsior/newbie/mon/elf_fighter");
		new("/wizards/excelsior/newbie/weapons/spiked_long_sword")->move(mon);
		new("/wizards/excelsior/newbie/armor/sweater")->move(mon);
		new("/wizards/excelsior/newbie/armor/pants")->move(mon);
		new("/wizards/excelsior/newbie/armor/shoes")->move(mon);
		new("/wizards/excelsior/obj/level")->move(mon);
		mon->set_skill("two handed blade",17);
		mon->force_me("wear sweater");
		mon->force_me("wear pants");
		mon->force_me("wear shoes");
		mon->force_me("wield sword in right hand and left hand");
		mon->set_money("silver",20);
		mon->move(this_object());
	}
}

void create() {
	::create();
	set_property("light",1);
	set_property("indoors",0);
	set_property("no castle",1);
	set("short","By a corrupted brook");
	set("long","What you thought to be a clear, bubbling brook has turned "+
		"out to be black in color. The water looks to be anything but "+
		"healthy. All life around the brook seems to have died as a result "+
		"of the brook's disgusting color. Looking upstream you see the "+
		"towering buildings of New Faerie Dust and realize the source of "+
		"this natural disaster- yet another side effect to large urban "+
		"areas running off not-fully-developed magical power.");
	set_smell("default","The dead plant life gives off pungant odors.");
	set_listen("default","You hear a brook, and it is right here.");
	set_items((["woods":"They are destroyed here.",
		"brook":"You may be able to 'drink' water from this brook, though "+
			"this may not be wise.",
		({"plant life","life"}):"It is all dead.",
		"new faerie dust":"Its towers lume in the distance upstream." ]));
	set_exits((["west":"/wizards/excelsior/newbie/rooms/fr3.2",
		"south":"/wizards/excelsior/newbie/rooms/fr4.3"]));
}

void init() {
	::init();
	add_action("drink","drink");
}

int drink(string str) {
	if(str[0..4] != "water") {
		notify_fail("Type 'drink water' to drink from the brook.\n");
		return 0;
	}
	write("You drink from the brook. Ug! It tastes really bad!");
	write("%^GREEN%^You have been poisoned by the polluted water!");
	this_player()->add_poisoning(5);
	return 1;
}
