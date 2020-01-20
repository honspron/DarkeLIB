//           Maxwell's Underground Mud Library
//                 Guardian of Silver Altar


#include "/adm/include/std.h"
inherit MONSTER;
object money;
create() {
    ::create();
   set_name("dravack");
   set_id( ({ "guardian","guard","dwarf","dravack" }) );
   set_short("Dravack the guardian of the silver altar");
   set_level(25);
   set_max_hp(5000);
   set_hp(5000);
   add_skill("two handed polearm",150);
   set("long", " Dravack stands before you. His presence radiates power "
   "and spreads fear into your very soul. As you look into his burning "
   "eyes you realize that you could never beat him alone.\n "
   "His thick silver body armour wraps around him, covered with paintings "
   "and strange writing. On his chest plate is an image of a glowing "
   "silver axe blade.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_body_type("dwarf");
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(15,
     ({ "Dravack adjusts his grip on the scythe.",
     "Dravack's eyes seem to glow dark red.",
     "Dravack adjusts his stance in front of the altar.",
     "Dravack spins his scythe in a large arc.",}),0 );
    set_achats(50,
    ({ "Dravack adjusts his grip on the scythe.",
     "Dravack steps to the side.",
     "Dravack grins evily.",
      "Dravack laughs at your pitiful attack techniques.",}) );
// Spell Code
    set_combat_chance(90);
    add_spell("blizzard", "$A");
    add_spell("fireball", "$A");
    add_spell("wrath of god", "$A");
    set_spell_level("blizzard", 6);
    set_spell_level("chaos storm", 6);   
    set_spell_level("wrath of god", 6);
// Skills For Spells
    add_skill("conjuration",75);
    add_skill("chaos magic",75);
    add_skill("prayer",75);
// Money Code
    money=new("std/obj/coins");
    money->set_money("gold",(random(100)+500));
    money->move(this_object());
}
void die(object who) {
  object mon,mik,wep1,wep;
  string here;
  here=file_name(environment(this_object()));
  tell_room(here,"Dravack stumbles back and glances at the ceiling.");
  tell_room(here,"Suddenly he bursts into flames and disappears in a "
  "cloud of ash!\n");
  this_object()->remove();
  ::die(who);
  return;
}

