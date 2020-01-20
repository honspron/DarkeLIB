/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       kaing.c
 * Location:   /wizards/mon/
 * Used in:    /wizards/room/
 * Power:      High in this Domain (26+)
 * Notes:      Devil Lord of the 22nd Circle
 *             "Striker of Spheres"
 */
#include <std.h>
inherit MONSTER;

void create() {
   int lev;
   object gem;
   ::create();
   lev = 30;
   set_property("zor_mon", 1);
   set_name("kaing");
   set("id", ({"kaing", "monolith", "monster"}) );
   set_level(lev);
   set_overall_ac(250);
   set("short", "Monolith of Kaing");
   set("long", @LONG
In shape this devil lord appears as a twelve foot tall,
black basalt, monolith.  He does not appear to have any
distinguishable features nor any noticable limbs.
LONG
);
   set_property("enhance criticals", -3);
   
   set("race", "devil");
   set_gender("neuter");
   set_alignment(-500);
   set_money("electrum", random(10000));
   set_languages( ({"common",}) );
   set_combat_chance(80);
   set_casting_chance(200);
   set_max_hp(25000);
   set_hp(25000);
   set_stats("strength",400);
   set_stats("dexterity",250);
   set_skill("perception", 250);
   set_skill("enchantment", 125);
   add_spell("implosion", "$A");
   set_spell_level("implosion", 6);
   set_skill("necromancy", 125);
   add_spell("lifesteal", "$A");
   set_spell_level("lifesteal", 6);
   add_spell("life drain", "$A");
   set_spell_level("life drain", 6);

   set_body_type("slime");
   set_emotes(5, ({
      "A screaming whisp of light is absorbed by the monolith.",
      "You are engulfed for a moment in utter darkness.",
      "You lovingly hear in your head, 'EMBRACETHEMONOLITH'",
    }), 0);
   set_achats(15, ({
      "You hear in your head, 'STRONGERMEYOURFIGHTINGMAKES'",
      "'LIVENOTYOUSHALL', rings out in your head.",
      "Your soul is darkened...you feel less experienced.",
    }) );
  set_property("melee damage", ([ "infernal" : 55, ]));
  gem = new("/wizards/zortek/canyon/obj/soul_gem");
  gem->set_devil_name("Kaing");
  gem->move(this_object());
}
