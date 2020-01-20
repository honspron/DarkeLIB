//           Maxwell's Underground Mud Library
//                  Dwarf Miner Cart Pusher


#include "/adm/include/std.h"
inherit MONSTER;

create() {
    ::create();
   set_name("Donkey");
   set_id( ({ "Donkey","donkey" }) );
   set_short("A strong brown Donkey.");
   set_level(15);
   set("long", "The Donkey is covered in dust and dirt.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_hp(750);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(6,
     ({ "The Donkey paws at the ground.",
     "The Donkey's tail swishes to the side.",
     "The Donkey shakes his head.",
     "The Donkey snorts.",}),0 );
   set_body_type("dwarf");
   set_achats(50,
    ({ "The Donkey snorts.",
     "The Donkey kicks up some dirt.",
     "The Donkey lowers his head.",}) );
//   add_limb("head", "FATAL", 50, 0, 4);
//   add_limb("torso", "FATAL", 50, 0, 4);
//   add_limb("right leg", "right hoof", 35, 0, 4);
//   add_limb("right hoof", "", 25, 0, 4);
//   add_limb("left leg", "left hoof", 35, 0, 4);   
//   add_limb("left hoof ", "", 25, 0, 4);
//   add_limb("rear right leg", "rear right hoof", 35, 0, 4);
//   add_limb("rear right hoof", "", 25, 0, 4);
//   add_limb("back left leg", "left hoof", 35, 0, 4);
//   add_limb("rear left hoof", "", 25, 0, 4);
   set_skill("dodge",100);
   set_skill("attack",100);
   set_skill("defense",100);
}



