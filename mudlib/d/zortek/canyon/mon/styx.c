/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       styx.c
 * Location:   /wizards/mon/
 * Used in:    /wizards/room/
 * Power:      High for this Domain (25+)
 * Notes:      Devil Lord
 */
#include <std.h>
inherit MONSTER;

void create() {
   int lev;
   ::create();
   lev = 25;
   set_level(lev);
   set_property("zor_mon", 1);
   set_property("enhance criticals", -3);
   set_name("devil");
   set("id", ({"devil", "styx devil", "monster"}) );
   set("short", "Styx Devil");
//---------------------------------------------------------
   set("long", @LONG
Lords in Residence of the fifth plane of Hell, Styx devils are humanoid
but with disproportionately large, ugly heads and wings of black trimmed
with silver.
LONG
);
   set("race", "devil");
   set_gender("male");
   set_overall_ac(190);
   set_alignment(-900);
   set_money("electrum", random(10000)+random(10000));
   set_languages( ({"common",}) );
   set_combat_chance(50);
   set_casting_chance(50);

   set_skill("elementalism", 250);
   add_spell("elemental storm", "");
   set_spell_level("elemental storm", 6);

   set_body_type("human");
   set_property("melee damage", ([ "aether" : 35, ]));
   set("aggressive", 0);
}

string query_element() { return "vacid"; }
