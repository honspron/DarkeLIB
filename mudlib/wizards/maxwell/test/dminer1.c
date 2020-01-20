//           Maxwell's Underground Mud Library
//                  Dwarf Miner Cart Pusher

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"

inherit MONSTER;
string here,play,play1,play2,name,race,race1; 

create() {
    ::create();
   set_name("Miner");
   set_id( ({ "Miner","dwarf","miner" }) );
   set_short("A stocky dwarf Miner");
   set_level(3);
   set("long", "The Miner is covered in dust and dirt.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_hp(300);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_body_type("dwarf");
   set_emotes(10,
     ({ "The Miner struggles with one of the mine carts.",
     "The Miner wipes the sweat from his eyes.",
     "The Miner glances at you suspiciously.",
     }),0 );
   set_achats(50,
     ({ "The Miner loses his balance.",
       "The Miner grunts.",
       "The Miner smiles wickedly.",
     }) );
  call_out("cart",3,this_player());
  set("aggressive", (: call_other, this_object(), "test" :) );
}
int cart(string fun){
   object me;
   if(present("cart")){
     me = this_object();
     me->force_me("pull lever"); 
     tell_room(UNDER+"2","The Miner pulls a lever on the side of the "
     "mine cart.");
     return 1;
   }
}
int test(object who) {
   here = file_name(environment(this_object()));
   play = (who->query_name());
//   play = (this_player()->query_name());
   race = (who->query_value());
   force_me("say cheese "+here+" "+play+" "+race);
   if(race == "dwarf") {
     play1 = play;
     race1 = race;
     call_out("test2",2,this_player());
     return 0;
   }
   if(race != "dwarf") { 
     play2 = play;
     call_out("attack",2,this_player());
    return 0;
   }
   return 0;
}
int test2() {   
   force_me("say You can pass "+play1+". Your a "+race1); 
   return 0;
//   return 1;
}
int attack() {
   force_me("say You don't belong here "+play2+". Prepare to die!!");
   return 0;
//   force_me("kill "+play2);
//   return 1;
}
