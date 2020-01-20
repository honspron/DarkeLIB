/* Weapon coded by Duridian for DarkeMud. */

#include <std.h>
inherit WEAPON;

void create() {
   ::create();
   set_name("dwarven two-handed sword");
   set("id", ({"dwarven two-handed sword", "two-handed sword", "sword"}) );
   set("short", "dwarven two-handed sword");
   set("long",
"This steel two-handed sword was crafted by the skilled dwarven "
"weaponsmith Dugar.  The blade is four feet in length, and the hilt is "
"nearly a foot long itself.");
   set_weight(250);
   set_value(450);
   set_type("two handed blade");
   set_wc(27, "cutting");
   set_ac(1);
   set_material("metal/steel");
   set_quality(4+random(2));
   set_verb("slice");
   set_hit_bonus(15);
   set_parry_bonus(-10);
   set_decay_rate(250);
   set_wield("Your grip the dwarven two-handed sword with both hands.");
   set_unwield("You loosen your grip on the dwarven two-handed sword.");
}
