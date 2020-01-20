// /wizards/excelsior/crits/hell
// for use with Aether crits. this file must be above

inherit "std/room";

void create() {
	::create();
	set_property("light",3);
	set_property("indoors",1);
	set("short","Somewhere very hot");
	set("long","You seem to be in an underground cavern of some sort. All around "+
		"hot pools of boiling magma bubble in small vat-like craters. Flames "+
		"occasionally burst out from various orifices around the cave. What could "+
		"this place be?");
	set_items((["magma":"After closer examination, you notice little demons bathing "+
			"it.",
		"flames":"What kind of hellish place is this?"]));
}

void reset() {
	if(!present("devil")) {
		new("/wizards/excelsior/crits/devil")->move(this_object());
	}
}
