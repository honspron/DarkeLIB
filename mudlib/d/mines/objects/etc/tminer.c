//           Maxwell's Underground Mud Library
//                     Dwarf Miner


#include <std.h>
#include <under.h>
inherit MONSTER;
inherit "/wizards/maxwell/objects/mon/mob_eq2";

object money;
create() {
    ::create();
   set_name("larry");
   set_id( ({ "larry","dwarf" }) );
   set_short("larry the test miner");
   set_level(20);
   set_max_hp(2500);
   set_hp(2500);
   set("long", "The Miner is covered in dust. His white beard is now "
    "a dark grey color.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set("aggressive", (: call_other, this_object(), "agres" :) );
   set_body_type("human");
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(10,
     ({ "The Miner examines the wall, searching for gems.",
     "The Miner uses a handkerchief to wipe the sweat from his eyes.",
     }),0 );
    set_achats(50,
    ({ "The Miner loses his balance.",
     "The Miner grunts.",
     "The Miner smiles wickedly.",}));
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
//Equipment Code
    mob = this_object();
    wield_hand = "right hand";
//Misc
    set_moving(1); 
    set_speed(60);
}
void die(object who) {
object ob;
  ob = new(UNETC+"dester");
  ob->move(this_object());
  call_other(ob,"nuke_environment");
  ::die(who);
  return;

}



