inherit "/std/vault";
#include "../walled_city.h"

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("duane")) {
      new(MON+"duane")->move(this_object());
   }
}

void create() {
	::create();
	set_property("indoors",1);
	set_property("light",3);
	add_exit(ROOMS+"grounds2", "south");
	set("short","Dwarf Duane's General Store");
	set("long",
	"This is the Duane's general Store.  Here, you can purchase "
	"the various items and sundries needed for day-to-day adventuring.  "
	"Several useful items are seen all about.");
	set_items( (["sign":"The say reads: 'say duane, help' for assistance."
	]) );
}

