//           Maxwell's Underground Mud Library
//                    Wolf Guard


#include "/adm/include/std.h"
inherit MONSTER;
object who2;
create() {
    ::create();
   set_name("grey wolf");
   set_id( ({ "wolf"}) );
   set_short("A large grey wolf");
   set_level(16);
   set("long", "The grey wolf looks very strong.");
   set_gender("male");
   set("race", "dog");
   set_alignment(0);
//   set_body_type("dwarf");
   set_wielding_limbs( ({"right hand","left hand"}) );
//   add_limb("head", "FATAL", 50, 0, 4);
//   add_limb("torso", "FATAL", 50, 0, 4);
//   add_limb("right leg", "right paw", 35, 0, 4);
//   add_limb("right paw", "", 25, 0, 4);
//   add_limb("left leg", "left paw", 35, 0, 4);   
//   add_limb("left paw ", "", 25, 0, 4);
//   add_limb("right rear leg", "right rear paw", 35, 0, 4);
//   add_limb("right rear paw", "", 25, 0, 4);
//   add_limb("back left leg", "left rear paw", 35, 0, 4);
//   add_limb("left rear paw", "", 25, 0, 4);
   set_emotes(10,
     ({ "The wolf growls softly.",
     "The wolf glances at you and drools.",
     "The wolf whines.",
     }),0 );
    set_achats(50,
    ({ "Grey wolf howls!.",
     "Grey wolf snarls!.",
     "Grew wolf bares his teeth!.",
     }) );
//    set_aggressive(0);
//  set("aggressive", (: call_other, this_object(), "attack" :) );
}
