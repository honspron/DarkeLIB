//           Maxwell's Underground Mud Library
//                     Dwarf Miner Sweeper


#include "/adm/include/std.h"
inherit MONSTER;

create() {
    ::create();
   set_name("Miner");
   set_id( ({ "dwarf","miner","sweeper","worker" }) );
   set_short("A dwarf worker");
   set_level(16);
   set("long", "This Miner is in charge of making sure the tracks "
   "stay clear of rubble and dust. He looks very dedicated.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_body_type("dwarf");
   set_emotes(10,
     ({ "The miner sweeps some debris off the track.",
     "The miner sweeps some debris into a neat little pile.",
     "The miner wipes some dirt off his clothing.",
     }),0 );
    set_achats(50,
    ({ "The Miner loses his balance.",
     "The Miner grunts.",
     "The Miner smiles wickedly.",
     }) );
}



