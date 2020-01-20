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
//--------------------------------------------------------------
int only_players(object who);
void init() {
  int x;
  ::init();
  x = only_players(this_player());
  if (x) force_me("kill "+this_player()->query_name());
} 


void create() {
   int lev;
   ::create();
   lev = random(10)+7;
   set_property("zor_mon", 1);
   set_name("bone");
   set("id", ({"bone", "devil", "bone devil", "monster" }) );
   set_level(lev);
   set("short", "a bone devil");
   set("long", @LONG
This is a lanky creature that gets its name sake from the
fact that its hide is thin and tightly conforms to its
skeletal frame.
LONG
);
   set("race", "devil");
   set_gender("neuter");
   set_alignment(-1*15*lev);
   set_money("silver", random(100)+12);
   set_languages( ({"common",}) );
   set_overall_ac(50);
   set_combat_chance(50);
   set_casting_chance(85);

   set_skill("magery", 10*lev+75);
   add_spell("fire shield", "$(ME)");
   set_spell_level("fire shield", 6);

   set_skill("conjuration", 10*lev+75);
   add_spell("internal flame", "$A");
   set_spell_level("internal flame", random(3)+3);

   set_body_type("devil");
   set_achats(15, ({
      "You are hit with staggering force by an invisible entity.",
      "Someone casts a spell and you feel less experienced.",
      "An invisible entity claws at your back.",
    }) );
  set_property("melee damage", ([ "impact" : 45, ]));
}
//---------------------------------------------------------

int only_players(object who) {
  int x = random(100);
  if(who->query_npc()) return 0;
  if(wizardp(who)) return 0;
  if(who->is_player()) {
    switch( (string)who->query_level() ) {
      case 0..2:  return 0;
      case 3..5:  if(x<25)  return 1; break;
      case 6..7:  if(x<50) return 1; break;
      case 8..10: if(x<55) return 1; break;
      case 11..13:if(x<60) return 1; break;
      case 14..16:if(x<65) return 1; break;
      case 17..19:if(x<70) return 1; break;
      case 20..22:if(x<75) return 1; break;
      case 23..25:if(x<80) return 1; break;
      case 26..28:if(x<85) return 1; break;
      case 29..31:if(x<90) return 1; break;
      case 32..35:if(x<60) return 1; break;
      default: return 1;
    }
  }
  else {
    return 0;
  }
}

