//           Maxwell's Underground Mud Library
//                Dwarf Miner Gem Polisher


#include "/adm/include/std.h"
#define WEAP "/wizards/maxwell/objects/weapons/"
inherit MONSTER;
object money;
create() {
    ::create();
   set_name("Miner");
   set_id( ({ "Miner","dwarf","miner" }) );
   set_short("A strong dwarf Miner");
   set_level(20);
   set("long", "The Miner is cleaning several small gems.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_body_type("dwarf");
   set_emotes(10,
      ({ "The Miner polishes a gem.",
      "The Miner wipes the sweat from his eyes.",
      "The Miner blows on the side of the gem.",}),0 );
    set_achats(50,
      ({ "The Miner loses his balance.",
      "The Miner grunts.",
      "The Miner smiles wickedly.",}) );
// Spell Code
    set_combat_chance(80);
    add_spell("explosive fireball", "$A");
    set_spell_level("explosive fireball", 6);   
// Skills For Spells
    add_skill("conjuration",75);
// Money Code
    money=new("std/obj/coins");
    money->set_money("gold",(random(100)+500));
    money->move(this_object());
//Weapon Code
    switch(random(2)){
      case 0:new(WEAP+"spear")->move(this_object());
             force_me("wield spear in right hand and left hand");
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
void die(object who) {
  string here;
  tell_room(environment(this_object()),
    "Miner's body shakes violently.",({ this_object() }));
  ::die(who);
  return;
}



