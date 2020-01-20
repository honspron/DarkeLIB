// /wizards/excelsior/newbie/rooms/fr1.2

inherit "std/room";

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set_property("ex newbie",1);
	set_property("no castle",1);
	set("short","By a transporter");
	set("day long","You have wandered into the forest of Wayreth. Everything "+
		"is very bright and green here. Butterflies flutter in the air. "+
		"There is no pollution or any sign of a destructive presence. It "+
		"seems like a very happy place. Looking to your northeast however, "+
		"you are able to catch glimses of the oppressive towers of New "+
		"Faerie Dust and remember that you are standing by a magical portal "+
		"that can take you right back to that unbearable place.");
	set("night long","You have wandered into the forest of Wayreth. Everything "+
		"is very peaceful here at night. When you look up into the air you "+
		"see stars shining with all their might. Looking to your northeast however, "+
		"you are able to catch glimses of the oppressive lighted towers of New "+
		"Faerie Dust and remember that you are standing by a magical portal "+
		"that can take you right back to that unbearable place.");
	set_listen("default","You hear the hum of the portal and the sound of birds in "+
		"the air");
	set_smell("default","The air smells very fresh here.");
	set_items((["portal":"It will take you back to the Excelsior Emporium.",
		"new faerie dust":"You can just see it through the trees.",
		"towers":"They are very tall",
		"butterflies":"They make you feel happy. Heeheehee!",
		"stars":"They make you feel peaceful. You practically fall asleep but "+
			"hit you head on a rock."]));
	set_exits((["portal":"/wizards/excelsior/rooms/emporium/newbie",
		"northeast":"/wizards/excelsior/newbie/rooms/fr2.1",
		"east":"/wizards/excelsior/newbie/rooms/fr2.2",
		"southeast":"/wizards/excelsior/newbie/rooms/fr2.3"]));
}
