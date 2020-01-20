/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       mephit.c
 * Location:   /wizards/mon/
 * Used in:    /wizards/room/path*
 * Power:      Low for Domain (10+)
 * Notes:      Should be used in groups
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
void create() {
   int lev;
   ::create();
   lev = random(3)+3;
   set_property("zor_mon", 1);
   set_name("mephit");
   set("id", ({"mephit"}) );
   set_level(lev);
   set("short", "a mephit");
   set("long", @LONG
This is a small and sleek devilish creature with black oily skin
and short stringy hair.  This creature looks sly and small, but its
bite may be worse than its bark.  The flames licking its claws looks
a bit unnerving.
LONG
);
   set("race", "devil");
   set_gender("neuter");
   set_alignment(-1*lev*25);
   set_money("copper", random(lev*50)+17);
   set_languages( ({"common","devilish"}) );
   set_combat_chance(50);
   set_casting_chance(90);

   set_skill("", random(lev*10)+75);
   add_spell("", "$A");
   set_spell_level("", 1);

   set_body_type("devil");
   set_emotes(5, ({
    }), 0);
   set_achats(15, ({
    }) );
  set_property("melee damage", ([ "" : 5, ]));
  set_speed(150);
  set_moving(1);
}
//---------------------------------------------------------

int only_players(object who) {
  int x = random(100);
  if(who->query_npc()) return 0;
  if(wizardp(who)) return 0;
  if(who->is_player()) {
    switch( (string)who->query_level() ) {
      case 0..2:  return 0;
      case 3..5:  if(x<5)  return 1; break;
      case 6..7:  if(x<10) return 1; break;
      case 8..10: if(x<25) return 1; break;
      case 11..13:if(x<30) return 1; break;
      case 14..16:if(x<45) return 1; break;
      case 17..19:if(x<50) return 1; break;
      case 20..22:if(x<55) return 1; break;
      case 23..25:if(x<60) return 1; break;
      case 26..28:if(x<65) return 1; break;
      case 29..31:if(x<70) return 1; break;
      case 32..35:if(x<75) return 1; break;
      default: return 1;
    }
  }
  else {
    return 0;
  }
  return 0;
}
