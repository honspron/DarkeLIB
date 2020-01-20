//           Maxwell's Underground Mud Library
//                     Dwarf Miner Sweeper


#include "/adm/include/std.h"
inherit MONSTER;
object mon;
create() {
    ::create();
   set_name("Miner");
   set_id( ({ "dwarf","miner","sweeper" }) );
   set_short("A dwarf miner");
   set_level(3);
   set("long", "This Miner is in charge of making sure the tracks "
   "stay clear of rubble and dust. He looks very dedicated.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_hp(300);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(10,
     ({ "The miner sweeps some debris off the track.",
     "The miner pushes some debris into a neat little pile.",
     "The miner wipes some dirt off his clothing.",
     }),0 );
   set_achats(50,({ "The Miner loses his balance.",
     "The Miner grunts.",
     "The Miner smiles wickedly.",}) );
   set_body_type("dwarf");
   call_out("inv",2,this_object());
}
void inv(){
object mon;
   mon = this_object();
   if(present("broom")){
     mon->force_me("get broom");
     mon->force_me("wield broom in right hand");
   }
   if(!present("broom")){
      new("/wizards/maxwell/objects/weapons/broom")->move(mon);
      mon->force_me("wield broom in right hand");
  }
   if(present("gloves")){
      mon->force_me("get gloves");
      mon->force_me("wear gloves");
   }
   if(!present("gloves")){
      new("/wizards/maxwell/objects/armour/gloves")->move(mon);
      mon->force_me("wear gloves");
   }
 
}


