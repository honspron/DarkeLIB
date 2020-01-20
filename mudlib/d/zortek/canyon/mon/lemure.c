/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       bone.c
 * Location:   /wizards/mon/
 * Used in:    Canyon
 * Power:      Low for Domain (14+)
 * Notes:      Minor rank 3 devil that should
 *             be used in clusters or for support.
 */

#include <std.h>
inherit MONSTER;
int only_players(object who);

void init() {
  int x;
  ::init();
  x = only_players(this_player());
  if (x) force_me("kill "+this_player()->query_name());
} 
//--------------------------------------------------------------
void create() {
   int lev;
   ::create();
   lev = random(7)+7;
   set_property("zor_mon", 1);
   set_name("lemure");
   set("id", ({"lemure", "devil", "lemure devil", "monster" }) );
   set_level(lev);
   set("short", "a sluggish lemure");
   set("long", @LONG
The creature before you would best be described as an animated
blob of festering puss, jelled fluids, and slime.  The creature
reeks of rot and decay and leaves a slighly damp trail when it
moves.  Its face is formless and it is difficult to determine
where it is actually "looking" at any given time.
LONG
);
   set("race", "devil");
   set_gender("neuter");
   set_alignment(-1*15*lev);
   set_money("silver", random(100)+12);
   set_languages( ({"common","devilish"}) );
   set_combat_chance(50);
   set_casting_chance(85);
   set_skill("body alteration", 10*lev+50);
   add_spell("instill poison", "$A");
   set_spell_level("instill poison", 6);

   set_skill("necromancy", 10*lev+50);
   add_spell("cold blast", "$A");
   set_spell_level("cold blast", 6);

   set_body_type("slime");
   set_achats(15, ({
      "%^BOLD%^CYAN%^Lemure casts a spell.%^RESET%^\nA foul mist enshrouds you.",
      "%^BOLD%^CYAN%^Lemure casts a spell.%^RESET%^\nYou feel less experienced.",
      "%^BOLD%^CYAN%^Lemure casts a spell.%^GREEN%^\nYou take damage from a toxic mist.%^RESET%^",
    }) );                              
  set_property("melee damage", ([ "cold" : 35, ]));
}
//---------------------------------------------------------
/* The Lemure are the despised of the damned.  They are
 * retched creatures that while are quite annoying are used
 * for the primary grunt work of the higher ranked damned.
 * They are very unpredictable and may attack just as much
 * out of stupidity or mistaken identity as they will from
 * a command from their superior.  They will; however, not
 * combat other monsters except on a fumble (Standard Devil)
 * 
 * Lemure tend to frighten easily and stand a greater chance
 * of attacking someone based on their perception of the power
 * of those in their presence.
 */
int only_players(object who) {
  int x = random(80);
  if(who->query_npc()) return 0;
  if(wizardp(who)) return 0;
  if(who->is_player()) {
    switch( (string)who->query_level() ) {
      case 0..5:  return 0;
      case 6..10:  if(x<10) return 1; break;
      case 11..15:if(x<20) return 1; break;
      case 16..20:if(x<30) return 1; break;
      case 21..25:if(x<40) return 1; break;
      case 26..30:if(x<50) return 1; break;
      case 31..35:if(x<60) return 1; break;
      default: return 1;
    }
  }
  else {
    return 0;
  }
  return 0;
}


