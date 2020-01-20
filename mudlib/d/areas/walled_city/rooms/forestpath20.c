#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

	set_property("light", 2);
	set_property("outdoors", 1);

       set("short", "Forest path.");
       set("long", "You stand in a forest. To the north the trees appear burnt and blackened, stripped bare of their foliage. To the east the path decends deeper into the forest.");

       add_exit(ROOMS+"dirtpath1","north");
       add_exit(ROOMS+"forestpath19","east");
 
	set_items(([
	({ "leaf", "leaves", "foliage" }) :
	"The leaves here usually grow large and thick, but trees to the north have been burnt bare of all foliage.",
	({ "tree", "trees" }) :
	"The trees stand stark against the sky, branches blackened by fire."
	]));

	set_smell("default", "The smell of a recent fire is strong here.");
	

}
