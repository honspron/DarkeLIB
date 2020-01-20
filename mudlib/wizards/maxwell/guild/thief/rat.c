//           Maxwell's Underground Mud Library
//                    Sewer rat


#include "/adm/include/std.h"
#include "under.h"
inherit MONSTER;

create() {
    ::create();
   set_name("rat");
   set_id( ({ "rat","sewer rat"}) );
   set_short("a slimy sewer rat");
   set_level(1);
   set("long", "The disgusting large rodent is scurryin along the "
      "wall, trying to avoid you.");
   set_gender("male");
   set("race", "rodent");
   set_alignment(0);
   set_wielding_limbs( ({"right paw","left paw"}) );
   set_body_type("quadruped");
   set_emotes(10,
     ({ "The rat scurries quietly.",
     "The rat glances at you with its bead little eyes",
     }),0 );
}

