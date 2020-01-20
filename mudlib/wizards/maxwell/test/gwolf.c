//           Maxwell's Underground Mud Library
//                     Wolf Guard


#include "/adm/include/std.h"
inherit MONSTER;

create() {
    ::create();
   set_name("Mikarty");
   set_id( ({ "Mikarty","dwarf","guard","mikarty" }) );
   set_short("Mine guard Mikarty");
   set_level(17);
   set("long", "Mikarty is standing before you wearing the traditional "
    "uniform of a Dwarf security officer.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set("aggressive", 0);
   set_body_type("dwarf");
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(10,
     ({ "Mikarty glances at his wolf.",
     "Mikarty mumbles something about tresspassers in the other tunnel.",
     "Mikarty picks at something under his nail.",}),0 );
   set_achats(50,
    ({ "Mikarty loses his balance.",
     "Mikarty grunts.",
     "Mikarty smiles wickedly.",}) );
}

