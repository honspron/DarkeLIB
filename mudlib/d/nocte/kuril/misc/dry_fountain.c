#include <move.h>
inherit "/std/Object";

void create() {
  	::create();
  	set_name("dry fountain");
  	set_id(({ "fountain", "dry fountain" }) );
  	set_short("%^BLUE%^%^BOLD%^A dry fountain%^MAGENTA%^%^BOLD%^");
  	set_long(
		"A dried out fountain with a large tree growing inside it.  "
		"the trees roots have shattered the inside of the fountain "
		"into rubble.  Looking down into the dry fountain, the "
		"bottom is almost ten feet down.  Must have been one "
		"deep fountain."
 	);
	set_weight(1000000);
	set_value(0);
}

int clean_up() { return 0; }
