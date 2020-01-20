//	Wizard:  Glitch
//	Trolltown
//	hole.c

#include <std.h>

inherit ROOM;

void create() {
	::create();
	set_property("light", 0);
	set_property("indoors", 1);
	set("short", "Hole");
	set("long", "You are in a deep hole beneth the chiefs hut. The walls"+
	" are bare dirt, as is the floor and ceiling.  A ladder leads back "+
	"up.");
	add_exit("c_hut","up");
	set_items(([
	"dirt" : "Slightly damp earth.",
	({ "wall","walls" }) : "They are made of dirt.",
	({ "floor","ceiling" }) : "They are made of dirt.",
	({ "ladder" }) : "A heavy wooden ladder, crudely constructed.",
	]));
	set_smell("default","You smell damp earth.");
	set_listen("default","You hear the sound of heavy breathing.");
}
