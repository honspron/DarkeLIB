#include <std.h>
#include "../walled_city.h"
inherit "std/room";

void create() {
     ::create();
     set_property("light", 3);
     set_property("indoors", 3);

	set("short", "Walled city.");
	set("long", "The shops at the north end of this makeshift town are to the east and west. Here, in the northern section people gather to buy sell and trade goods and services. This is what the dwarves believe to be thier metropolis!");

	add_exit(ROOMS+"grounds8","south");
	add_exit(ROOMS+"grounds3","east");
	add_exit(ROOMS+"grounds5","west");
	set_items(([
	({ "city" }) :
		"The city is alive albeit on the side of a mountain.",
	({ "room", "walls", "floor" }) :
		"This area like most, is alive with the dwarves going about their daily chores."
	]));
	set_smell("default", "You are sure you smell charred meat somewhere.");
	set_listen("default", "You hear merchants calling out to the townsfolk, hawking their wares.");

}
