#include <std.h>
#include "../walled_city.h"
inherit ROOM;

void create() {
::create();

  set_property("outdoors", 1);

    set("short", "Forest clearing.");
    set("long", "You must not have been paying close attention. Suddenly things do not appear as they did just moments ago. Somehow you have stumbled upon a campsite. A small fire smolders in the center of this tiny clearing deep within the forest. All around you trees, nothing but trees, stretching endlessly before you in every direction but here someone has cleared the forest floor of debris and made camp.");
   add_exit(ROOMS+"forestpath5","east");
set_items(([
({ "leaf", "leaves" }) :
"The leaves here grow large and thick, and block out all natural light from the sky.",
({ "tree", "trees" }) :
"The mighty oaks stand tall above the forest floor.",
({ "fire", "campfire" }) :
  "A small campfire in a dirt pit surrounded by rocks burns fitfully, giving off clouds of smoke.",
({ "camp", "campsite" }) :
"A tiny clearing deep within the forest with a small fire burning smokily."
]));
set_smell("default", "Woodsmoke fills the air.");
set_listen("default", "You hear the snapping and crackling of burning wood.");

}
