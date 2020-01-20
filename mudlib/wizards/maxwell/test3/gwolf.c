//           Maxwell's Underground Mud Library
//                     Wolf Guard


#include "/adm/include/std.h"
#define WEAP "/wizards/maxwell/objects/weapons/"
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
     ({ "Mikarty glances around.",
     "Mikarty mumbles something about tresspassers in the other tunnel.",
     "Mikarty flexes a muscle.",
     }),0 );
    set_achats(50,
    ({ "Mikarty loses his balance.",
     "Mikarty grunts.",
     "Mikarty smiles wickedly.",
     }) );

    switch(random(2)){
      case 0:new(WEAP+"spear")->move(this_object());
             force_me("wield spear in right hand and left hand");
             break;
      case 1:new(WEAP+"handaxe")->move(this_object());
             force_me("wield axe in right hand");
             break;
    }
    switch(random(3)){
      case 0:new("d/damned/virtual/leather-jacket.armour")->
                 move(this_object());
             force_me("wear jacket");
             break;
      case 1:new("d/damned/virtual/leather-vest.armour")->
                 move(this_object());
             force_me("wear vest");
             break;
      case 2:new("d/damned/virtual/leather-pants.armour")->
                 move(this_object());
             force_me("wear pants");
             break;
    }



}

