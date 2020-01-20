// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit "/wizards/nevin/std/kuril_river";

void reset() {
	::reset();
	if(!present("fowl")) { new(MON+"fowl")->move(TO); }
}

void create() {
	::create();
	set_property("indoors", 0);
	set_property("light", 3);
	set_property("night light", -2);
	set_property("no castle", 1);
	set("short", "River Near Kuril");
	set("long",
		"Flowing around a bend in the river, you float westward "
		"toward the ocean.  Bird nests line the cliff walls."
	);
	set_items( ([
		"ocean": "It is to the west.",
		({"cliffs", "cliff"}): "They rise almost straight up toward "
			"the city above you.",
		({"birds", "bird"}): "They flit about catching insects to "
			"eat.  Hmm...perhaps they are actually bats",
		"insects": "They appear to be just small spots flying about "
			"near the river.",
		({"nests", "nest"}): "Perched upon small outcroppings of rocks "
			"or bored right into the muddy banks, there are "
			"countless numbers of them along the river bank.",
		"river": "It flows swiftly past the city of death as if it "
			"too did not wish to remain too close to that "
			"accursed place."
	]) );
	set_listen("default", "You hear the flowing of water.");
	set_exits( ([
		"northeast": ROOMS+"r22",
		"west": ROOMS+"r24"
	]) );
}
