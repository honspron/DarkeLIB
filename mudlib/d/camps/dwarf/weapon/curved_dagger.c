/* Weapon coded by Duridian for DarkeMud. */

#include <std.h>
inherit WEAPON;

void create() {
   mixed str;
   ::create();
   set_name("curved dagger");
   set("id", ({"curved dagger", "dagger",}) );
   set("short", "curved dagger");
   set("long",
   "This steel dagger has a curved, double-edged blade that comes to a "
   "razor-sharp point at the tip.");
   set_weight(50);
   set_value(750);
   set_type("knife");
   set_wc(10, "impaling");
   set_ac(1);
   set_quality(5);
   set_material("metal/steel");
   set_verb("rip");
   set_hit_bonus(15);
   set_parry_bonus(-5);
   set_decay_rate(275);
   set_hit( (: call_other, this_object(), "weapon_hit" :) );
   set_property("enchantment", 1);
   str = ({ ({"You notice some magical writing on the weapon that reads: \"Koboldum Fatalum\".\n", "detect magic" }) });
   set_property("extra long", str);
   set_wield("The curved dagger hums for a moment as you grip its handle.");
   set_unwield("You hear a soft hum as you unwield the curved dagger.");
}

int weapon_hit(object attacker) {
   if(random(2) == 0) {
      if(lower_case((string)attacker->query_race()) == "kobold") {
         message("info", "The kobold shrieks in pain as the curved dagger "+
                         "rips its flesh!", environment(attacker));
         return(15+random(10));
      }
   }
}

int restore_me(string file) {
  ::restore_me(file);
  set_hit( (: call_other, find_object_or_load("/wizards/duridian/dwarf/weapon/curved_dagger"), "weapon_hit" :) );
  return 1;
}

