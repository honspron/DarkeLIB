// /wizards/excelsior/cape/rooms/town4

#include <std.h>

inherit ROOM;

void create() {
	set_property("indoors",0);
	set_property("light",3);
	set("short","On the town");
	set("long","The main road through town continues to meandor at this "+
		"very spot at which you stand. To the southeast it follows the natural "+
		"curve of a short slope down to town square. To the northeast it travels "+
		"to a large gate. Hrm. To the west is a weapons and armour shop. A picket "+
		"fence to the side of the road catches your eye.");
	set_items((["road":"It is cobblestone.",
		"slope":"It has a vertical fall of about 5 feet.",
		"shop":"If you need weapons or armour (and everyone does!) go there.",
		"gate":"You'lll have to get closer to get a good look at it.",
		"fence":"It is perfectly white and fits in with the theme of the town "+
			"perfectly! There is a pretty rose bush growing beside it. Hrm.",
		({"bush","roase bush"}):"It is a very nice rose bush. One stem in "+
			"particular catches your eye.",
		"stem":"You have no idea why this stem stood out among the others. You "+
			"notice one of the leaves on this stem looks peculiar.",
		({"leaf","leave"}):"You take a closer look at the leaf and realize that "+
			"it looked peculiar because there is a ladybug on it!",
		({"bug","ladybug"}):"It is a pretty red and black lady bug. One of the ladybug's "+
			"spots catches you eye.",
		"spot":"Of the bug's 6 spots, you have no idea why you attention was drawn "+
			"to this one. After examining to spot, you notice a tiny flaw in it!",
		"flaw":"The spot should be totally black, but this tiny speck is white! "+
			"There is a dust mite on the speck.",
		({"mite","dust mite","dustmite"}):"MAN you have good eyesight! Jesus!"]));
	set_exits((["northeast":"/wizards/excelsior/cape/rooms/town5",
		"southeast":"/wizards/excelsior/cape/rooms/town3",
		"west":"/wizards/excelsior/cape/rooms/weapon_shop"]));
}
