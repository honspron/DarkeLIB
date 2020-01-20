//           Maxwell's Underground Mud Library
//                  Dwarf Miner Cart Pusher

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
#define WEAP "/wizards/maxwell/objects/weapons/"
inherit MONSTER;
string here,play,play1,play2,name,race,race1; 
object money;
create() {
    ::create();
   set_name("Miner");
   set_id( ({ "Miner","dwarf","miner" }) );
   set_short("A stocky dwarf Miner");
   set_level(20);
   set("long", "The Miner is covered in dust and dirt.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_body_type("dwarf");
   set_emotes(10,
     ({ "The Miner struggles with one of the mine carts.",
     "The Miner wipes the sweat from his eyes.",
     "The Miner glances at you suspiciously.",}),0 );
   set_achats(50,
     ({ "The Miner loses his balance.",
       "The Miner grunts.",
       "The Miner smiles wickedly.",}) );
  call_out("cart",3,this_player());
  set("aggressive", (: call_other, this_object(), "test" :) );
// Spell Code
    set_combat_chance(80);
    add_spell("ice dagger", "$A");
    add_spell("fireball", "$A");
    set_spell_level("ice dagger", 6);
    set_spell_level("fireball", 6);   
// Skills For Spells
    add_skill("conjuration",75);
// Money Code
    money=new("std/obj/coins");
    money->set_money("gold",(random(100)+500));
    money->move(this_object());
//Weapon Code
    switch(random(2)){
      case 0:new(WEAP+"sledge")->move(this_object());
             force_me("wield sledge in right hand and left hand");
             break;
      case 1:new(WEAP+"handaxe")->move(this_object());
             force_me("wield axe in right hand");
             break;
    }
//Amour Code
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
   race = (who->query_race());
   if(race == "dwarf") {
    if(who->is_player()){
     play1 = play;
     race1 = race;
     call_out("test2",2,this_player());
    }
    return 0;
   }
   if(race != "dwarf") { 
    if(who->is_player()){
     play2 = play;
     call_out("attack",2,this_player());
    }
   return 0;
   }
   return 0;
}
int test2() {   
   force_me("say You don't look like any "+race1+" I know!"); 
   force_me("kill "+play1);
   return 1;
}
int attack() {
   force_me("say You don't belong here "+play2+". Prepare to die!!");
   force_me("kill "+play2);
   return 1;
}
void die(object who) {
  string here;
  tell_room(environment(this_object()),
    "Miner takes his last gasp of air.",({ this_object() }));
  ::die(who);
  return;
}
