/* Weapon coded by Duridian for DarkeMud. */

#include <std.h>
inherit WEAPON;

void create() {
   ::create();
   set_name("dwarven longsword");
   set("id", ({"dwarven longsword", "longsword", "sword"}) );
   set("short", "dwarven longsword");
   set("long",
"This longsword is yet another one of the fine creations of a skilled "
"dwarven weaponsmith.  The long, narrow blade ends with a razor-sharp "
"point and looks as if it could cut through just about anything.");
   set_weight(150);
   set_value(250);
   set_type("blade");
   set_wc(23, "cutting");
   set_wc(5, "impaling");
   set_ac(1);
   set_quality(3+random(3));
   set_material("metal/steel");
   set_verb("cut");
   set_hit_bonus(10);
   set_parry_bonus(10);
   set_decay_rate(250);
   set_wield("You grip the leather hilt of the dwarven longsword.");
   set_unwield("The leather hilt of the dwarven longsword creaks slightly as you loosen your grip on the weapon.");
}
