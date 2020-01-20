/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       quu.c
 * Location:   /wizards/mon/
 * Used in:    /wizards/room/
 * Power:      High for this Domain (25+)
 * Notes:      Devil Lord of 45th Circle
 *             "He that Roars"
 */
#include <std.h>
inherit MONSTER;

void init() {
  ::init();
  set("aggressive", random(2));
}

void create() {
   int lev;
   ::create();
   lev = 50;
   set_property("zor_mon", 1);
   set_name("quu");
   set("id", ({"quu", "lord quu", "Lord", "Quu", "monster"}) );
   set_level(lev);
   set("short", "Lord Quu");
//---------------------------------------------------------
   set("long", @LONG
In form this Devil is a large, shambling beast of great
similarity to that of a massive lizard.  His exterior is
thick hide of interwoven fiberous matter that he has been
known to shed on occation.
LONG
);
   set_max_hp(2750);
   set_hp(2750);
   set_max_mp(3500);
   set_mp(3500);
   set("race", "devil");
   set_gender("male");
   set_alignment(-900);
   set_money("electrum", random(10000));
   set_languages( ({"common",}) );
   set_combat_chance(50);
   set_casting_chance(150);

   set_skill("elementalism", 150);
   add_spell("greater elemental storm", "$A");
   set_spell_level("greater elemental storm", 6);

   set_body_type("human");
   set_emotes(5, ({
      "'ROOOOAAAAARRRR', bellows the Devil Lord.",
      "Lord Quu scratches his fiberous body.",
      "Several lumenous eyes peer at you.",
    }), 0);
   set_achats(15, ({
      "Quu threatens, 'Don't burn me...'",
      "Lord Quu rips out a piece of your soul.",
      "A deafening roar causes you to lose experience.",
    }) );
  set_property("melee damage", ([ "infernal" : 50, ]));
  set("aggressive", 0);
}

string query_element() {
  string *tmp;
  
    tmp = ({ "fire", "wind", "ice", "vacid", "water" });
    return tmp[random(sizeof(tmp))];
}
